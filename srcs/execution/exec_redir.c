/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:35:06 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/28 20:38:20 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	adjust_fd_for_redir(t_data *data, t_redir *redir, t_token *token, \
			int fd)
{
	if (redir->type == T_INFILE)
		put_fd_token(data, token, fd, token->out);
	else
		put_fd_token(data, token, token->in, fd);
}

int	do_redir(t_data *data, t_token *token, t_list *current)
{
	int			fd;
	const char	*redir_file;
	int			opening_flags;
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
		adjust_fd_for_redir(data, redir, token, fd);
	return (EXIT_SUCCESS);
}

int	check_redirection_files(t_data *data, t_token *token)
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
		if (ft_isemptystr(redir->string) || !ft_strcmp(redir->string, "''"))
		{
			printerr_source("", "No such file or directory");
			update_last_return(data, EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		code = do_redir(data, token, current);
		if (code != EXIT_SUCCESS)
			return (code);
		current = current->next;
	}
	return (code);
}
