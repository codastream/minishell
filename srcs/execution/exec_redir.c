#include "shell.h"

int	do_redirs(t_data *data, t_token *token, t_list *redir_list, int opening_flag)
{
	int					fd;
	t_list			*current;
	const char	*redir_file;

	if (!redir_list)
		return (EXIT_IGNORE);
	current = redir_list;
	while (current)
	{
		redir_file = (const char *) current->content;
		fd = open(redir_file, opening_flag, 0644);
		if (fd < 0)
		{
			token->command->has_invalid_redir = true;
			handle_strerror(data, (char *)redir_file, EXIT_FAILURE, false); // verifier si genere bien No such file or directory et Permission Denied
			return (EXIT_FAILURE);
		}
		else
		{
			if (opening_flag == O_RDONLY) // if redirin
				put_fd_token(data, token, fd, token->out);
			else
				put_fd_token(data, token, token->in, fd);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
/*
int redir_data(t_data *data, t_tree **tree_p)
 {
 	code = do_redirs(data, tree, tree->value->command->redir_in, O_RDONLY);
 	code = do_redirs(data, tree, tree->value->command->redir_out_truncate, O_CREAT | O_WRONLY | O_TRUNC);
 	code = do_redirs(data, tree, tree->value->command->redir_out_append, O_CREAT | O_RDONLY | O_APPEND);
	return (code);
}*/

int	check_redirection_files(t_data *data, t_token **tokens, t_token *token)
{
	int	code;

	(void) tokens;
	if (token->type != T_COMMAND)
		return (EXIT_IGNORE);
	code = do_redirs(data, token, token->command->redir_in, O_RDONLY);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_redirs(data, token, token->command->redir_out_truncate, O_CREAT | O_WRONLY | O_TRUNC);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_redirs(data, token, token->command->redir_out_append, O_CREAT | O_RDONLY | O_APPEND);
	return (code);
}
