#include "shell.h"

int		wait_all(t_data *data, t_exec *exec)
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
	if (data->return_code && data->return_code != 0)
		code = data->return_code;
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
	if (command->pathname && command->has_invalid_redir == false)
	{
		// printf(" before exec\n");
		safe_dup2(data, token->in, STDIN_FILENO);
		safe_dup2(data, token->out, STDOUT_FILENO);
		pop_all_fd(&(data->fds));
		free_data(data);
		execve((const char *) command->pathname, \
		command->command_args, env_local);
	}
	handle_child_error(data, command);
}

void  put_fd(t_data *data, t_tree **tree, int in, int out)
{
	(*tree)->value->out = out;
//	printf("-> %d\n-> %d\n\n", in, out)
  if ((*tree)->value->type == T_COMMAND && (*tree)->value->command->heredoc)
    fd_push_back(&(data->fds), in);
  else
  {
    (*tree)->value->in = in;
	  fd_push_back(&(data->fds), in);
  }
	fd_push_back(&(data->fds), out);
//  printf("in--> %d\n out-->%d\n\n", in, out);
	(void)data;
}

void	do_redirs(t_data *data, t_tree *tree, t_list *redir_list, int opening_flag)
{
	int					fd;
	t_list			*current;
	const char	*redir_file;

	if (!redir_list)
		return ;
	current = redir_list;
	while (current)
	{
		redir_file = (const char *) current->content;
		fd = open(redir_file, opening_flag, 0644);
		if (fd < 0)
		{
			tree->value->command->has_invalid_redir = true;
			ft_printfd(2, "%s: %s\n", strerror(errno), redir_file);
		}
		else
			put_fd(data, &tree, tree->value->in, fd);
		current = current->next;
	}
}

void  redir_data(t_data *data, t_tree **tree_p)
{
	// int fd;
	t_tree	*tree;

	tree = *tree_p;
	// if (tree->value->command->redir_in && !tree->value->command->heredoc)
		do_redirs(data, tree, tree->value->command->redir_in, O_RDONLY);
		// fd = open((*tree)->value->command->redir_in, O_RDONLY, 0644);
		// if (fd < 0)
		// {
		// 	(*tree)->value->command->has_invalid_redir = true;
		// 	printf("%s: %s\n", strerror(errno), (*tree)->value->command->redir_in);
		// }
		// put_fd(data, tree, fd, (*tree)->value->out);
	// }
	// if (tree->value->command->redir_out_truncate)
		do_redirs(data, tree, tree->value->command->redir_out_truncate, O_CREAT | O_WRONLY | O_TRUNC);
	// {
	// 	fd = open((*tree)->value->command->redir_out_truncate, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// 	if (fd < 0)
	// 	{
	// 		(*tree)->value->command->has_invalid_redir = true;
	// 		printf("%s: %s\n", strerror(errno), (*tree)->value->command->redir_out_truncate);
	// 	}
	// 	put_fd(data, tree, (*tree)->value->in, fd);
	// }
	// if (tree->value->command->redir_out_append)
	do_redirs(data, tree, tree->value->command->redir_out_append, O_CREAT | O_RDONLY | O_APPEND);
	// {
	// 	fd = open((*tree)->value->command->redir_out_append, O_CREAT | O_WRONLY | O_APPEND, 0644);
	// 	if (fd < 0)
	// 	{
	// 		(*tree)->value->command->has_invalid_redir = true;
	// 		printf("%s: %s\n", strerror(errno), (*tree)->value->command->redir_out_append);
	// 	}
	// 	put_fd(data, tree, (*tree)->value->in, fd);
	// }
 // init_heredoc(data, tree);
}

void	exec_command(t_data *data, t_tree *tree)
{
	int	child_pid = 1;

  if (tree->value->command->has_invalid_redir == false)
  {
	child_pid = safe_fork(data);
  	if (child_pid == 0)
		  child_exec(data, tree->value->command, tree->value);
	  else
  		data->exec->last_pid = child_pid;
  }
}

void  exec_pipe(t_data *data, t_tree *tree)
{
	int	fds[2];

	safe_pipe(data, fds);
	tree->value->pipe_read = fds[0];
	tree->value->pipe_write = fds[1];
	put_fd(data, &(tree->left), tree->value->in, fds[1]);
  put_fd(data, &(tree->right), fds[0], tree->value->out);
	exec_tree_node(data, tree->left);
	// print_pretty_tree(data, data->tree, 0, "root", true);
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
		// printf("*command detected\n");
    redir_data(data, &tree);
		exec_command(data, tree);
	}
}


int	exec_line(t_data *data, t_tree *tree)
{
	t_exec	*exec;
	int		code = 0;

	exec = init_exec(data, tree);
	data->exec = exec;
	if (!tree->left && !tree->right && is_builtin(data, tree->value->command))
	{
		redir_data(data, &tree);
		try_exec_single_builtin(data, tree->value, tree->value->command);
		return (data->return_code);
	}
	tree->value->in = 0;
	tree->value->out = 1;
	if (heredoc(data, &tree) != 0)
		return (130);
//  print_pretty_tree(data, tree, 0, "root", true);
	exec_tree_node(data, tree);
	// ft_put_green("exec_line before wait all\n");
	code = wait_all(data, data->exec);
	pop_all_fd(&(data->fds));
	return (code);
}
