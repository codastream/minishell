#include "shell.h"

int	do_redir(t_data *data, t_token *token, t_list *current)
{
	int	fd;
	const char	*redir_file;
	int	opening_flags;
	t_redir		*redir;

	redir = (t_redir *) current->content;
	if (redir->type == T_INFILE)
		opening_flags = O_RDONLY;
	else if (redir->type == T_OUTFILE_APPEND)
		opening_flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (redir->type == T_OUTFILE_TRUNCATE)
		opening_flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		return (EXIT_IGNORE);
	redir_file = (const char *) redir->string;
	fd = open(redir_file, opening_flags, 0666);
	if (fd < 0)
	{
		token->command->has_invalid_redir = true;
		handle_strerror(data, (char *)redir_file, EXIT_FAILURE, false);
		return (EXIT_FAILURE);
	}
	else
	{
		if (redir->type == T_INFILE) // if redirin
		{
			put_fd_token(data, token, fd, token->out);
		}
		else
			put_fd_token(data, token, token->in, fd);
	}
	return (EXIT_SUCCESS);
}

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
		fd = open(redir_file, opening_flag, 0666);
		if (fd < 0)
		{
			token->command->has_invalid_redir = true;
			handle_strerror(data, (char *)redir_file, EXIT_FAILURE, false); // verifier si genere bien No such file or directory et Permission Denied
			return (EXIT_FAILURE);
		}
		else
		{
			if (opening_flag == O_RDONLY) // if redirin
			{
				put_fd_token(data, token, fd, token->out);
			}
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

int	check_redirection_files(t_data *data, t_token *token)
{
	int		code;
	t_list	*current;

	// (void) tokens;
	if (token->type != T_COMMAND)
		return (EXIT_IGNORE);
	code = EXIT_SUCCESS;
	current = token->command->redirections;
	while (current)
	{
		code = do_redir(data, token, current);
		current = current->next;
	}

	// code = do_redirs(data, token, token->command->redir_in, O_RDONLY);
	// code = do_redirs(data, token, token->command->redir_out_truncate, O_CREAT | O_WRONLY | O_TRUNC);
	// // if (code != EXIT_SUCCESS)
	// // 	return (code);
	// code = do_redirs(data, token, token->command->redir_out_append, O_CREAT | O_WRONLY | O_APPEND);
	return (code);
}
