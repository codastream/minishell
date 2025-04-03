/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:20:57 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:21:06 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	assign_fd(t_data *data, t_tree *pipenode, t_tree *tree, bool is_left)
{
	int	in;
	int	out;

	if (is_left)
		in = pipenode->value->in;
	else
		in = pipenode->value->pipe_read;
	if (is_left)
		out = pipenode->value->pipe_write;
	else
		out = pipenode->value->out;
	if (has_redirin(tree))
		in = tree->value->in;
	if (has_redirout(tree))
		out = tree->value->out;
	fd_push_back(&data->fds, pipenode->value->pipe_read);
	fd_push_back(&data->fds, pipenode->value->pipe_write);
	put_fd_token(data, tree->value, in, out);
}
