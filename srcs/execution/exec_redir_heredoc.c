/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:35:55 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/08 21:23:39 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	is_empty_redir(t_data *data, t_redir *redir, t_token *token)
{
	if (ft_isemptystr(redir->string) || !ft_strcmp(redir->string, "''"))
	{
		printerr_source("", "No such file or directory");
		token->command->has_invalid_redir = true;
		update_last_return(data, EXIT_FAILURE);
		return (true);
	}
	return (false);
}

int	do_heredoc(t_data *data, t_token *token, t_list *current)
{
	int			fd;
	const char	*redir_file;
	t_redir		*redir;
	int			code;

	redir = (t_redir *) current->content;
	redir_file = (const char *) redir->string;
	if (redir->type != T_EOF)
		return (EXIT_SUCCESS);
	else
		fd = init_heredoc(data, current, redir);
	if (fd < 0)
	{
		token->command->has_invalid_redir = true;
		check_signal_ok(data);
		code = get_last_return(data);
		if (code < 128)
			handle_strerror(data, (char *)redir_file, code, false);
		return (EXIT_FAILURE);
	}
	if (has_next_of_same_type(current, redir))
		close(fd);
	else
		adjust_fd_for_redir(data, redir, token, fd);
	return (EXIT_SUCCESS);
}

int	prepare_heredoc(t_data *data, t_token *token)
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
		code = do_heredoc(data, token, current);
		if (code != EXIT_SUCCESS)
			return (code);
		current = current->next;
	}
	return (code);
}
