/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:35:06 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/08 17:04:00 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	adjust_fd_for_redir(t_data *data, t_redir *redir, t_token *token, \
			int fd)
{
	if (redir->type == T_INFILE || redir->type == T_EOF)
		put_fd_token(data, token, fd, token->out);
	else
		put_fd_token(data, token, token->in, fd);
}

int	get_opening_flags(t_redir *redir)
{
	int			opening_flags;

	if (redir->type == T_INFILE)
		opening_flags = O_RDONLY;
	else if (redir->type == T_OUTFILE_APPEND)
		opening_flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (redir->type == T_OUTFILE_TRUNCATE)
		opening_flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		return (EXIT_IGNORE);
	return (opening_flags);
}

bool	has_next_of_same_type(t_list *current, t_redir *current_redir)
{
	t_redir	*next_redir;
	t_list	*next;

	while (current)
	{
		next = current->next;
		if (next)
		{
			next_redir = (t_redir *) next->content;
			if ((is_input_redir(current_redir) && is_input_redir(next_redir)) \
				|| (is_output_redir(current_redir) \
					&& is_output_redir(next_redir)))
				return (true);
		}
		current = current->next;
	}
	return (false);
}

int	do_redir(t_data *data, t_token *token, t_list *current)
{
	int			fd;
	const char	*redir_file;
	int			opening_flags;
	t_redir		*redir;

	redir = (t_redir *) current->content;
	redir_file = (const char *) redir->string;
	if (redir->type == T_EOF)
		return (EXIT_IGNORE);
	else
	{
		opening_flags = get_opening_flags(redir);
		fd = open(redir_file, opening_flags, 0666);
	}
	if (fd < 0)
	{
		token->command->has_invalid_redir = true;
		handle_strerror(data, (char *)redir_file, EXIT_FAILURE, false);
		return (EXIT_FAILURE);
	}
	if (has_next_of_same_type(current, redir))
		close(fd);
	else
		adjust_fd_for_redir(data, redir, token, fd);
	return (EXIT_SUCCESS);
}

int	prepare_redirs(t_data *data, t_token *token)
{
	int		code;
	t_list	*current;
	t_redir	*redir;

	if (token->type != T_COMMAND)
		return (EXIT_IGNORE);
	code = EXIT_SUCCESS;
	current = token->command->redirections;
	while (current)
	{
		redir = (t_redir *) current->content;
		if (is_empty_redir(data, redir, token))
			return (ERROR_EMPTY_REDIR);
		code = do_redir(data, token, current);
		if (code != EXIT_SUCCESS)
			return (code);
		current = current->next;
	}
	return (code);
}
