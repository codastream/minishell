#include "shell.h"

int		wait_all(t_exec *exec)
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
		if (result == exec->last_pid)
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

	exec = ft_calloc(1, sizeof(t_exec));
	check_alloc(data, exec);
	count = 0;
	iter_tree_count(tree, &count, count_if_command);
	exec->commands_nb = count;
	exec->current_cmd_index = 0;
	return (exec);
}

// void  close_all(t_tree *tree)
// {
//   if (tree->value->in >= 0)
//     close(tree->value->in);
//   if (tree->value->out >= 0)
//     close(tree->value->out);
//   if (tree->left)
//     close_all(tree->left);
//   if (tree->right)
//     close_all(tree->right);
// }

void	child_exec(t_data *data, t_command *command, t_token *token)
{
	char	**env_local;

	env_local = hashtab_to_tab(data, data->vars);
	check_alloc(data, env_local);
	if (!command->command_name) // empty command with redir
		exit (EXIT_SUCCESS);
	try_exec_builtin(data, token, command);
	command->pathname = get_checked_pathmame(data, command);
	if (command->pathname)
	{
		printf(" before exec\n");
		dup2(token->in, STDIN_FILENO);
		dup2(token->out, STDOUT_FILENO);
		execve((const char *) command->pathname, \
		command->command_args, env_local);
	}
	else
	{
		handle_invalid_command(data);
	}
	ft_free_2d_char_null_ended(env_local);
}

void	exec_command(t_data *data, t_tree *tree)
{
	int	child_pid;

	printf("*exec command : %s\n", tree->value->string);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		ft_put_yellow("child starting\n");
		// TODO handle redirs
		child_exec(data, tree->value->command, tree->value);
	}
	else
	{
		data->exec->last_pid = child_pid;
	}
}

void  exec_pipe(t_data *data, t_tree *tree)
{
	safe_pipe(data, data->exec->fds);
	tree->left->value->out = data->exec->fds[1];
	tree->left->value->in = tree->value->in;
	tree->right->value->in = data->exec->fds[0];
	tree->right->value->out = tree->value->out;
	exec_tree_node(data, tree->left);
	close(data->exec->fds[1]);
	print_pretty_tree(data, tree, 0, "", true);
	exec_tree_node(data, tree->right);
	close(data->exec->fds[0]);
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
		printf("*command detected\n");
		exec_command(data, tree);
	}
}


int	exec_line(t_data *data, t_tree *tree)
{
	t_exec	*exec;
	int		code;

	exec = init_exec(data, tree);
	data->exec = exec;
	printf("%sstart of execution --- storing STDIN in %d and STDOUT in %d%s\n", P_PINK, exec->original_in, exec->original_out, P_NOC);
	if (!tree->left && !tree->right && is_builtin(tree->value->command))
	{
		try_exec_single_builtin(data, tree->value, tree->value->command);
		// return(0); // code won't be accessed
	}
	exec->original_in = dup(STDIN_FILENO);
	exec->original_out = dup(STDOUT_FILENO);
	iter_tree_modify(tree, init_fds);
	tree->value->in = 0;
	tree->value->out = 1;
	exec_tree_node(data, tree);
	code = wait_all(data->exec);
	safe_dup2(data, exec->original_in, STDIN_FILENO);
	safe_dup2(data, exec->original_out, STDOUT_FILENO);
	return (code);
}
