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
//		if (result == last_cpid)
	//		code = WEXITSTATUS(status);
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

void  close_all(t_tree *tree)
{
  if (tree->value->command->in < 0)
    close(tree->value->command->in);
  if (tree->value->command->out < 0)
    close(tree->value->command->out);
  if (tree->left)
    close_all(tree->left);
  if (tree->right)
    close_all(tree->right);
}

void	child_exec(t_data *data, t_command *command)
{
	char	**env_local;

	env_local = hashtab_to_tab(data, data->vars);
	check_alloc(data, env_local);
	if (!command->command_name) // empty command with redir
		exit (EXIT_SUCCESS);
	command->pathname = get_checked_pathmame(data, command);
	// try_exec_builtin(data, command);
	if (command->pathname)
	{
		printf(" before exec\n");
//		debug_fd(data, exec);
    dup2(command->in, STDIN_FILENO);
	  dup2(command->out, STDOUT_FILENO);
	  execve((const char *) command->pathname, \
		command->command_args, env_local); 
	}
	else
	{
		handle_invalid_command(data);
	}
  //free env_local
  close_all(data->tree);
}

void	exec_command(t_data *data, t_tree *tree)
{
	int	child_pid;

	// safe_pipe(data, exec->fds);
	printf("*exec command : %s\n", tree->value->string);
//	printf("%snew pipe with read %d and write %d%s\n", P_PINK, exec->fds[0], exec->fds[1], P_NOC);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		ft_put_yellow("child starting\n");
		child_exec(data, tree->value->command);
	}
	else
	{
	//	exec->last_pid = child_pid;
	}
}

void  exec_tree_node(t_data *data, t_tree *tree);

void  exec_pipe(t_data *data, t_tree *tree)
{
  int fds[2];

  safe_pipe(data, fds);
  tree->left->value->command->out = fds[1];
  tree->left->value->command->in = tree->value->command->in;
  tree->right->value->command->in = fds[0];
  tree->right->value->command->out = tree->value->command->out;
  exec_tree_node(data, tree->left);
  close(fds[1]);
  
  exec_tree_node(data, tree->right);
  close(fds[0]);
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
	if (!tree->left && !tree->right && is_buildins(tree->value->command))
	{
		try_exec_first_buildins(data, tree->value->command);
		return(0);
	}
  tree->value->command->in = 0;
  tree->value->command->out = 1;
	exec_tree_node(data, tree);
	code = wait_all(data->exec);
  close_all(tree);
	return (code);
}
