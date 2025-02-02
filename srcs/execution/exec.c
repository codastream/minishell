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

bool	is_invalid_redir(t_command *command)
{
	int		code;
	bool	invalid;

	invalid = false;
	if (command->redir_in)
	{
		code = access(command->redir_in, R_OK);
		if (code < 0)
			invalid = true;
	}
	return (invalid);
}

void	try_init_infile(t_exec *exec, t_command *command)
{
	int	fd;

	if (!command->redir_in)
		return ;
	fd = open(command->redir_in, O_RDONLY, 0555);
	if (fd < 0)
	{
		exec->future_fdin = STDIN_FILENO;
		command->has_invalid_redir = true;
	}
	else
	{
		exec->future_fdin = dup(fd);
		close(fd);
	}
}

void	try_init_outfile(t_exec *exec, t_command *command)
{
	int		fd;

	if (!command->redir_out_truncate || !command->redir_out_append)
		return ;
	if (command->redir_out_truncate && access(command->redir_out_truncate, W_OK) == 0)
		fd = open(command->redir_out_truncate, O_WRONLY | O_TRUNC, 077);
	else if (command->redir_out_append && access(command->redir_out_append, W_OK) == 0)
		fd = open(command->redir_out_append, O_WRONLY | O_APPEND, 0777);
	else if (command->redir_out_truncate)
		fd = open(command->redir_out_truncate, O_WRONLY | O_CREAT);
	else
		fd = open(command->redir_out_append, O_WRONLY | O_CREAT);
	if (fd < 0)
	{
		exec->future_fdout = STDOUT_FILENO;
		command->has_invalid_redir = true;
	}
	else
	{
		exec->future_fdout = dup(fd);
		close(fd);
	}
}

bool	is_last_command(t_exec *exec)
{
	return (exec->current_cmd_index == exec->commands_nb - 1);
}

void	exec_command(t_data *data, t_exec *exec, t_command *command)
{
	// int	exec_code;

	close(exec->fds[0]);
	close(exec->fds[1]);
	try_init_infile(exec, command);
	try_init_outfile(exec, command);
	// toto check path
	if (command->has_invalid_redir)
	{
		close(exec->fds[0]);
		close(exec->fds[1]);
		handle_error(data, "invalid file");
	}
	if (command->pathname)
	{
		execve((const char *) command->pathname, \
			command->command_args, NULL); // todo add envparams
	}
	else
	{
		handle_invalid_command(data);
	}
}

void	do_parent(t_exec *exec)
{
	close(exec->future_fdin);
	exec->future_fdin = dup(exec->fds[0]);
	close(exec->fds[0]);
	close(exec->fds[1]);
}

void	exec_pipe(t_data *data, t_exec *exec, t_tree *tree)
{
	int	child_pid;
	safe_pipe(data, exec->fds);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{ // todo check for invalid redir out
		safe_dup2(data, exec->future_fdin, STDIN_FILENO);
		if (is_last_command(exec))
			safe_dup2(data, exec->future_fdout, STDOUT_FILENO);
		else
			safe_dup2(data, exec->fds[1], STDOUT_FILENO);
		exec_command(data, exec, tree->right->value->command);
	}
	else
	{
		exec->last_pid = child_pid;
		do_parent(exec);
	}
}

void	exec_tree_node(t_data *data, t_exec *exec, t_tree *tree)
{
	if (!tree)
		return ;
	exec_tree_node(data, exec, tree->left);
	if (tree->value->type == T_PIPE)
		exec_pipe(data, exec, tree);
	else if (tree->value->type == T_COMMAND)
		exec_command(data, exec, tree->value->command);
	exec_tree_node(data, exec, tree->right);
}

int	exec_ins(t_data *data, t_tree *tree)
{
	t_exec	*exec;
	int		code;

	exec = init_exec(data, tree);
	check_alloc(data, exec);
	data->exec = exec;
	exec_tree_node(data, data->exec, tree);
	code = wait_all(data->exec, data->exec->last_pid);
	return (code);
}
