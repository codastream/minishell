#include "shell.h"

t_exec	*init_exec(t_tree *tree)
{
	t_exec	*exec;
	int	count;

	count = 0;
	exec = ft_calloc(1, sizeof(t_exec));
	check_alloc(exec);
	iter_tree_count(tree, &count, count_if_command);
	exec->commands_nb = count;
	exec->current_cmd_index = 0;
	return (exec);
}

bool	is_invalid_redir(t_command *command)
{
	char	*file;
	int		code;
	bool	invalid;

	invalid = false;
	if (command->redir_in)
	{
		code = access(command->redir_in, R_OK);
		if (code < 0)
			invalid = true;
	}
}

void	try_init_infile(t_exec *exec, t_command *command)
{
	int	fd;

	if (!command->redir_in)
		return ;
	fd = open(command->redir_in, O_RDONLY, 0555);
	if (fd < 0)
	{
		exec->future_fdin;
		command->has_invalid_redir = true;
	}
	else
	{
		exec->future_fdin = dup(fd);
		close(fd);
	}
}

void	exec_command(t_exec *exec, t_command *command)
{
	close(exec->fds[0]);
	close(exec->fds[1]);
	try_init_infile(exec, command);
}

void	exec_pipe(t_exec *exec, t_tree *tree)
{
	exec->last_pid = safe_fork();
}

void	exec_ins(t_tree *tree)
{
	t_exec	*exec;

	exec = init_exec(tree);
	while (tree->left && tree->left->left)
		tree = tree->left;
	if (tree->value->type == T_PIPE)
		exec_pipe(exec, tree);

}
