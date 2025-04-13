/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:15:11 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:54:16 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	put_fd_heredoc(t_data *data, t_tree **tree, int in, int out)
{
	(*tree)->value->in = in;
	(*tree)->value->out = out;
	fd_push_back(&(data->fds), in);
	fd_push_back(&(data->fds), out);
	(void) data;
}

char	*get_last_eofmarker(t_command *command)
{
	t_list	*current;
	t_redir	*redir;
	char	*eof;

	eof = NULL;
	current = command->redirections;
	while (current)
	{
		redir = (t_redir *) current->content;
		if (redir->type == T_EOF)
			eof = redir->string;
		current = current->next;
	}
	return (eof);
}
