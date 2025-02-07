#include "shell.h"

int		wait_all(t_exec *exec, int last_cpid)
{
	int		status;
	pid_t	result;
	int		code;
	int 	i;

	code = EXIT_SUCCESS;
	i = 0;
	while (i < exec->commands_nb)
	{
		result = waitpid(0, &status, 0);
		if (result == last_cpid)
			code = WEXITSTATUS(status);
		i++;
	}
	if (exec->return_code && exec->return_code != 0)
		code = exec->return_code;
	return (code);
}

t_exec	*init_exec(t_data *data, t_tree *tree)
{
	t_exec	*exec;
	int	count;

	count = 0;
	exec = ft_calloc(1, sizeof(t_exec));
	check_alloc(data, exec);
	iter_tree_count(tree, &count, count_if_command);
	exec->commands_nb = count;
	exec->current_cmd_index = 0;
	// exec->future_redirin = -1;
	// exec->future_redirout = -1;
	return (exec);
}

// bool	is_invalid_redir(t_command *command)
// {
// 	int		code;
// 	bool	invalid;

// 	invalid = false;
// 	if (command->redir_in)
// 	{
// 		code = access(command->redir_in, R_OK);
// 		if (code < 0)
// 			invalid = true;
// 	}
// 	return (invalid);
// }

void	restore_in_out(t_data *data, t_exec *exec)
{
	(void) data;
	dup2(exec->original_in, STDIN_FILENO);
	printf("new fd %d = original STDIN %d\n", exec->original_in, STDIN_FILENO);
	dup2(exec->original_out, STDOUT_FILENO);
	printf("new fd %d = original STDOUT %d\n", exec->original_out, STDOUT_FILENO);
}

bool	is_last_command(t_exec *exec)
{
	return (exec->current_cmd_index == exec->commands_nb - 1);
}

void	init_in(t_data *data, t_exec *exec, t_command *command)
{
	int	fd;

	(void) exec;
	if (!command->redir_in && !command->heredoc)
	{
		safe_dup2(data, exec->fds[0], STDIN_FILENO);
		return ;
	}
	// TOOD heredoc
	if (command->redir_in)
	{
		fd = open(command->redir_in, O_RDONLY, 0555);
		printf("new fd for infile %d\n", fd);
		if (fd < 0)
		{
			close(exec->fds[0]);
			close(exec->fds[1]);
			handle_error(data, "invalid output file");
		}
		else
		{
			safe_dup2(data, fd, STDIN_FILENO);
			close(exec->fds[0]);
		}
	}
}

void	init_out(t_data *data, t_exec *exec, t_command *command)
{
	int		fd;

	(void) data;
	if (!command->redir_out_truncate && !command->redir_out_append)
	{
		if (!is_last_command(exec))
			safe_dup2(data, data->exec->fds[1], STDOUT_FILENO);
		return ;
	}
	if (command->redir_out_truncate)
	{
		fd = open(command->redir_out_truncate, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		printf("new fd for redir out > %d\n", fd);
	}
	else // supposing there can be only one kind of out redir
	{
		fd = open(command->redir_out_append, O_WRONLY | O_APPEND | O_CREAT, 0644);
		printf("new fd for redir out >> %d\n", fd);
	}
	if (fd < 0)
	{
		close(exec->fds[0]);
		close(exec->fds[1]);
		handle_error(data, "invalid output file");
	}
	else
	{
		safe_dup2(data, fd, STDOUT_FILENO);
		close(exec->fds[1]);
	}
}

// bool	has_redir_out(t_command *command)
// {
// 	if (command->redir_out_append || command->redir_out_truncate)
// 		return (true);
// 	return (false);
// }

void	do_child(t_data *data, t_exec *exec, t_command *command)
{
	char	**env_local;

	env_local = hashtab_to_tab(data, data->vars);
	check_alloc(data, env_local);
	ft_put_yellow("child init in and out\n");
	init_in(data, exec, command);
	init_out(data, exec, command);
	exec->current_cmd_index++;
	if (!command->command_name) // empty command with redir
		exit (EXIT_SUCCESS);
	command->pathname = get_checked_pathmame(data, command);
	try_exec_buildins(data, command);
	if (command->pathname)
	{
		execve((const char *) command->pathname, \
			command->command_args, env_local);
	}
	else
	{
		handle_invalid_command(data);
	}
}

void	do_parent(t_data *data, t_exec *exec)
{
	// ft_put_pink("parent restore STDIN / STDOUT\n");
	// restore_in_out(data, exec);
	// ft_put_pink("parent read -> STDOUT\n");
	// safe_dup2(data, exec->fds[0], STDIN);
	if (!is_last_command(exec))
		safe_dup2(data, exec->fds[0], STDIN_FILENO);
	else
		close(exec->fds[0]);
	close(exec->fds[1]);
	(void) data;
}

void	exec_pipe(t_data *data, t_exec *exec, t_tree *tree)
{
	int	child_pid;

	safe_pipe(data, exec->fds);
	printf("%sparent pipe with read %d and write %d%s\n", P_PINK, exec->fds[0], exec->fds[1], P_NOC);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		do_child(data, exec, tree->value->command);
	}
	else
	{
		exec->last_pid = child_pid;
		do_parent(data, exec);
	}
}

void	exec_tree_node(t_data *data, t_exec *exec, t_tree *tree)
{
	if (!tree)
		return ;
	printf("goto left\n");
	exec_tree_node(data, exec, tree->left);
	if (tree->value->type == T_PIPE)
	{
		printf("\tpipe detected goto right\n");
		exec_pipe(data, exec, tree->right); // or exec tree node ?
	}
	else if (tree->value->type == T_COMMAND)
	{
		printf("\texec command : %s\n", tree->value->string);
		exec_pipe(data, exec, tree);
	}
	printf("goto right\n");
	exec_tree_node(data, exec, tree->right);
}

int	exec_line(t_data *data, t_tree *tree)
{
	t_exec	*exec;
	int		code;

	exec = init_exec(data, tree);
	check_alloc(data, exec);
	exec->original_in = dup(STDIN_FILENO);
	exec->original_out = dup(STDOUT_FILENO);
	printf("%sstart of execution --- storing STDIN in %d and STDOUT in %d%s\n", P_PINK, exec->original_in, exec->original_out, P_NOC);
	data->exec = exec;
	if (!tree->left && !tree->right && is_buildins(tree->value->command))
	{
		try_exec_first_buildins(data, tree->value->command);
		return(0);
	}
	exec_tree_node(data, data->exec, tree);
	code = wait_all(data->exec, data->exec->last_pid);
	dup2(exec->original_in, STDIN_FILENO);
	dup2(exec->original_in, STDOUT_FILENO);
	close(exec->original_in);
	close(exec->original_out);
	return (code);
}
