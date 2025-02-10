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
	return (exec);
}

void	restore_in_out(t_data *data, t_exec *exec)
{
	// (void) data;
	printf("restored fd %d to STDIN\n", exec->original_in);
	safe_dup2(data, exec->original_in, STDIN_FILENO);
	printf("restored fd %d to STDOUT\n", exec->original_out);
	safe_dup2(data, exec->original_out, STDOUT_FILENO);
}

bool	is_last_command(t_exec *exec)
{
	return (exec->current_cmd_index == exec->commands_nb - 1);
}

void	init_in(t_data *data, int fds[2], t_exec *exec, t_command *command)
{
	int	fd;

	(void) exec;
	close(exec->original_in);
	if (!command->redir_in && !command->heredoc)
	{
		printf("redir future %d to STDIN\n", exec->future_redirin);
		debug_fd(data, exec);
		safe_dup2(data, exec->future_redirin, STDIN_FILENO);
		close(fds[0]);
		return ;
	}
	// TODO heredoc
	if (command->redir_in)
	{
		fd = open(command->redir_in, O_RDONLY, 0555);
		printf("new fd for infile %d\n", fd);
		if (fd < 0)
		{
			close(fds[0]);
			close(fds[1]);
			handle_error(data, "invalid output file");
		}
		else
		{
			safe_dup2(data, fd, STDIN_FILENO);
			close(fds[0]);
		}
	}
}

void	init_out(t_data *data, int fds[2], t_exec *exec, t_command *command)
{
	int		fd;

	(void) data;
	// (void) exec;
	close(exec->original_out);
	if (!command->redir_out_truncate && !command->redir_out_append)
	{
		printf("init out no redir\n");
		if (is_last_command(exec))
		{
			printf("init out last command - redirecting output to STDOUT\n");
			safe_dup2(data, exec->future_redirout, STDOUT_FILENO);
			close(fds[1]);
		}
		else
		{
			printf("init out - not last command\n");
			safe_dup2(data, fds[1], STDOUT_FILENO);
		}
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
		close(fds[0]);
		close(fds[1]);
		handle_error(data, "invalid output file");
	}
	else
	{
		safe_dup2(data, fd, STDOUT_FILENO);
		close(fds[1]);
	}
}

void	do_child_exec(t_data *data, t_exec *exec, t_command *command)
{
	char	**env_local;

	(void) exec;
	env_local = hashtab_to_tab(data, data->vars);
	check_alloc(data, env_local);
	if (!command->command_name) // empty command with redir
		exit (EXIT_SUCCESS);
	command->pathname = get_checked_pathmame(data, command);
	// try_exec_builtin(data, command);
	if (command->pathname)
	{
		printf(" before exec\n");
		debug_fd(data, exec);
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
	if (!is_last_command(exec))
		safe_dup2(data, exec->fds[0], STDIN_FILENO);
	else
		close(exec->fds[0]);
	close(exec->fds[1]);
	(void) data;
}

void	exec_pipe_command(t_data *data, t_exec *exec, t_tree *tree)
{
	int	child_pid;

	// safe_pipe(data, exec->fds);
	printf("*exec command : %s\n", tree->value->string);
	printf("%snew pipe with read %d and write %d%s\n", P_PINK, exec->fds[0], exec->fds[1], P_NOC);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		ft_put_yellow("child starting\n");
		init_in(data, exec->fds, exec, tree->value->command);
		init_out(data, exec->fds, exec, tree->value->command);
		do_child_exec(data, exec, tree->value->command);
	}
	else
	{
		exec->last_pid = child_pid;
	}
}

void	exec_tree_node(t_data *data, t_exec *exec, t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->value->type == T_PIPE)
	{
		safe_pipe(data, exec->fds);
		printf("*pipe detected\n");
		printf(" pipe goto left\n");
		debug_fd(data, exec);
		exec_tree_node(data, exec, tree->left);
		debug_fd(data, exec);
		close(exec->fds[1]);
		printf(" pipe goto right\n");
		exec_tree_node(data, exec, tree->right);
	}
	else if (tree->value->type == T_COMMAND )
	{
		printf("*command detected\n");
		if (exec->future_redirin == -1)
		{
			exec->future_redirin = dup(exec->original_in);
			printf(" storing original STDIN in future redirin %d\n", exec->future_redirin);
		}
		debug_fd(data, exec);
		if (is_last_command(exec))
		{
			exec->future_redirout = dup(exec->original_out);
		}
		exec_pipe_command(data, exec, tree);
		if (is_last_command(exec))
		{
			close(exec->future_redirin);
			safe_dup2(data, exec->fds[0], STDOUT_FILENO);
		}
		else
		{
			exec->future_redirin = dup(exec->fds[0]);
			close(exec->fds[0]);
		}
		exec->current_cmd_index++;
	}
}

int	exec_line(t_data *data, t_tree *tree)
{
	t_exec	*exec;
	int		code;

	exec = init_exec(data, tree);
	check_alloc(data, exec);
	exec->future_redirin = -1;
	exec->future_redirout = -1;
	printf("%sstart of execution --- storing STDIN in %d and STDOUT in %d%s\n", P_PINK, exec->original_in, exec->original_out, P_NOC);
	data->exec = exec;
	if (!tree->left && !tree->right && is_buildins(tree->value->command))
	{
		try_exec_first_buildins(data, tree->value->command);
		return(0);
	}
	exec->original_in = dup(STDIN_FILENO);
	exec->original_out = dup(STDOUT_FILENO);
	exec_tree_node(data, data->exec, tree);
	code = wait_all(data->exec, data->exec->last_pid);
	restore_in_out(data, exec);
	return (code);
}
