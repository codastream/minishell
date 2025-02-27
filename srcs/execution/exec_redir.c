#include "shell.h"

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
			handle_strerror(data, (char *)redir_file, EXIT_FAILURE, false);
		}
		else
		{
			if (opening_flag == O_RDONLY) // if redirin
				put_fd(data, &tree, fd, tree->value->out);
			else
				put_fd(data, &tree, tree->value->in, fd);
		}
		current = current->next;
	}
}

void redir_data(t_data *data, t_tree **tree_p)
{
	t_tree	*tree;

	tree = *tree_p;
	do_redirs(data, tree, tree->value->command->redir_in, O_RDONLY);
	do_redirs(data, tree, tree->value->command->redir_out_truncate, O_CREAT | O_WRONLY | O_TRUNC);
	do_redirs(data, tree, tree->value->command->redir_out_append, O_CREAT | O_RDONLY | O_APPEND);
}
