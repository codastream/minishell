#include "shell.h"

int		wait_all(t_data *data, t_exec *exec)
{
	int		status;
	pid_t	result;
	int		code;
	int 	i;

	(void) data;
	code = EXIT_SUCCESS;
	i = 0;
	while (i < exec->commands_nb)
	{
		result = waitpid(0, &status, 0);
		if (result == exec->last_pid)
			code = WEXITSTATUS(status);
		i++;
	}
	// if (data->return_code && data->return_code != 0)
	// 	code = data->return_code;
	return (code);
}



void	child_exec(t_data *data, t_command *command, t_token *token)
{
	char	**env_local;
	int		exec_code;

	env_local = hashtab_to_tab(data, data->vars);
	check_alloc(data, env_local);
	data->varstab = env_local;
	if (!command->command_name || !command->command_args[0]) // empty command with redir
	{
		close(token->in);
		free_all_data(data);
		// free_after_exec(data);
		// free_vars_and_data(data);
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(command->command_name) == 0)
		handle_custom_error_source_exit(data, "", NULL, EXIT_CMD_NOT_FOUND);
	try_exec_builtin(data, token, command);
	check_executable(data, token);
	safe_dup2(data, token->in, STDIN_FILENO);
	safe_dup2(data, token->out, STDOUT_FILENO);
	pop_all_fd(&(data->fds));
	// free_vars_and_data(data);
	exec_code = execve((const char *) command->pathname, \
	command->command_args, env_local);
	if (exec_code != EXIT_SUCCESS)
	{
		handle_custom_error_source_exit(data, command->command_name, strerror(errno), EXIT_FAILURE);
	}
}

void	exec_command(t_data *data, t_tree *tree)
{
	int	child_pid = 1;

	if (PRINT == 1)
		print_pretty_tree(data, data->tree, 0, "root", true);
	if (check_redirection_files(data, data->tokens, tree->value) == 0)
		child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		setup_child_signal();
		if (tree->value->command->has_invalid_redir)
		{
			close(data->exec->fds[1]);
			close(data->exec->fds[0]);
			free_all_data(data);
			exit(EXIT_FAILURE);
		}
		child_exec(data, tree->value->command, tree->value);
	}
	else
		data->exec->last_pid = child_pid;
}

bool	has_redirin(t_tree *tree)
{
	return (tree->value->type == T_COMMAND && tree->value->command->redir_in);
}

bool	has_redirout(t_tree *tree)
{
	return (tree->value->type == T_COMMAND && (tree->value->command->redir_out_append || tree->value->command->redir_out_truncate));
}


void  exec_pipe(t_data *data, t_tree *tree)
{
	int	fds[2];

	safe_pipe(data, fds);
	tree->value->pipe_read = fds[0];
	tree->value->pipe_write = fds[1];
	if (!has_redirin(tree->left))
		put_fd_token(data, tree->left->value, tree->value->in, fds[1]);
	else
		put_fd_token(data, tree->left->value, tree->left->value->in, fds[1]);
	if (!has_redirout(tree->right))
		put_fd_token(data, tree->right->value, fds[0], tree->value->out);
	else
		put_fd_token(data, tree->right->value, fds[0], tree->right->value->out);
	exec_tree_node(data, tree->left);
	if (PRINT == 1)
		print_pretty_tree(data, data->tree, 0, "root", true);
	pop_fd(&(data->fds), fds[1]);
	exec_tree_node(data, tree->right);
	pop_fd(&(data->fds), fds[0]);
}

void	exec_tree_node(t_data *data, t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->value->type == T_PIPE)
	{
		exec_pipe(data, tree);
	}
	else if (tree->value->type == T_COMMAND )
	{
		exec_command(data, tree);
	}
}

void	exec_line(t_data *data, t_tree *tree)
{
	t_exec	*exec;
	int		code;

	exec = init_exec(data, tree);
	data->exec = exec;
	if (!tree->left && !tree->right && is_builtin(data, tree->value->command))
	{
		if (!do_for_tokens(data, data->tokens, check_redirection_files))
			try_exec_single_builtin(data, tree->value, tree->value->command);
		return ;
	}
	tree->value->in = 0;
	tree->value->out = 1;
	code = heredoc(data, &tree);
	if (code != 0)
		return ;
	if (PRINT == 1)
		ft_put_yellow("check redir files\n");
//	do_for_tokens(data, data->tokens, check_redirection_files);
	exec_tree_node(data, tree);
	code = wait_all(data, data->exec);
	pop_all_fd(&(data->fds));
	if (PRINT == 1)
		printf("code after wait %d\n", code);
	update_last_return(data, code);
}
