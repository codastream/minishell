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

void	init_builtins(t_data *data, t_exec *exec)
{
	char		**builtins;
	t_builtin	*builtin_f;

	builtins = ft_calloc(8, sizeof(char *));
	check_alloc(data, builtins);
	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "exit";
	builtins[3] = "env";
	builtins[4] = "pwd";
	builtins[5] = "unset";
	builtins[6] = "export";
	exec->builtins = builtins;
	builtin_f = ft_calloc(8, sizeof(t_builtin *));
	check_alloc(data, builtin_f);
	builtin_f[0] = ft_cd;
	builtin_f[1] = ft_echo;
	builtin_f[2] = ft_exit;
	builtin_f[3] = ft_env;
	builtin_f[4] = ft_pwd;
	builtin_f[5] = ft_unset;
	builtin_f[6] = ft_export;
	exec->builtin_ptrs = builtin_f;
}

t_exec	*init_exec(t_data *data, t_tree *tree)
{
	t_exec		*exec;
	int			count;

	exec = ft_calloc(1, sizeof(t_exec));
	check_alloc(data, exec);
	init_builtins(data, exec);
	count = 0;
	iter_tree_count(tree, &count, count_if_command);
	exec->commands_nb = count;
	exec->current_cmd_index = 0;
	return (exec);
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
		free_after_exec(data);
		free_vars_and_data(data);
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(command->command_name) == 0)
		handle_custom_error_source_exit(data, "", NULL, EXIT_CMD_NOT_FOUND);
	try_exec_builtin(data, token, command);
	try_navigation(data, token);
	command->pathname = get_checked_pathmame(data, command);
	if (command->pathname)
	{
		safe_dup2(data, token->in, STDIN_FILENO);
		safe_dup2(data, token->out, STDOUT_FILENO);
		pop_all_fd(&(data->fds));
		// free_vars_and_data(data);
		exec_code = execve((const char *) command->pathname, \
		command->command_args, env_local);
		if (exec_code != EXIT_SUCCESS)
		{
			handle_custom_error_source_exit(data, command->command_name, strerror(errno), EXIT_FAILURE);
			// perror("execve");

		}
		exit(EXIT_FAILURE);
	}
	else if (command->command_name)
		handle_custom_error_source_exit(data, command->command_name, MSG_CMD_NOT_FOUND, EXIT_CMD_NOT_FOUND);
}

void	exec_command(t_data *data, t_tree *tree)
{
	int	child_pid = 1;


	if (PRINT == 1)
		print_pretty_tree(data, data->tree, 0, "root", true);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
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
		do_for_tokens(data, data->tokens, check_redirection_files);
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
	do_for_tokens(data, data->tokens, check_redirection_files);
	exec_tree_node(data, tree);
	code = wait_all(data, data->exec);
	pop_all_fd(&(data->fds));
	if (PRINT == 1)
		printf("code after wait %d\n", code);
	update_last_return(data, code);
}
