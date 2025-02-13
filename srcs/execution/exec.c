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
	exec->return_code = EXIT_SUCCESS;
	return (exec);
}

void  close_all(t_tree *tree)
{
  if (tree->value->in < 0)
    close(tree->value->in);
  if (tree->value->out < 0)
    close(tree->value->out);
  if (tree->left)
    close_all(tree->left);
  if (tree->right)
    close_all(tree->right);
}

void	child_exec(t_data *data, t_command *command, t_token *token)
{
	char	**env_local;

	env_local = hashtab_to_tab(data, data->vars);
	check_alloc(data, env_local);
	data->varstab = env_local;
	if (!command->command_name) // empty command with redir
	{
		exit(EXIT_SUCCESS);
	}
	try_exec_builtin(data, token, command);
	command->pathname = get_checked_pathmame(data, command);
	if (command->pathname)
	{
		printf(" before exec\n");
		safe_dup2(data, token->in, STDIN_FILENO);
		safe_dup2(data, token->out, STDOUT_FILENO);
		pop_all_fd(&(data->fds));
		free_data(data);
		execve((const char *) command->pathname, \
		command->command_args, env_local);
	}
	else
	{
		handle_invalid_command(data);
	}
  //free env_local
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

void  exec_tree_node(t_data *data, t_tree *tree);

void  put_fd(t_data *data, t_tree **tree, int in, int out)
{
  (*tree)->value->in = in;
  (*tree)->value->out = out;
  printf("-> %d\n-> %d\n\n", in, out);
  fd_push_back(&(data->fds), in);
  fd_push_back(&(data->fds), out);
  (void)data;
}

void  exec_pipe(t_data *data, t_tree *tree)
{
  safe_pipe(data, data->exec->fds);
  put_fd(data, &(tree->left), tree->value->in, data->exec->fds[1]);
  put_fd(data, &(tree->right), data->exec->fds[0], tree->value->out);
  exec_tree_node(data, tree->left);
  print_pretty_tree(data, tree, 0, "root", true);
  pop_fd(&(data->fds), data->exec->fds[1]);
  exec_tree_node(data, tree->right);
  pop_fd(&(data->fds), data->exec->fds[0]);
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
		return (0);
	}
//  data->exec->original_in = dup(0);
//  data->exec->original_out = dup(1);
  tree->value->in = 0;
  tree->value->out = 1;
	exec_tree_node(data, tree);
	code = wait_all(data->exec);
  pop_all_fd(&(data->fds));
//  safe_dup2(data, data->exec->original_in, 0);
//  safe_dup2(data, data->exec->original_out, 1);
	return (code);
}
