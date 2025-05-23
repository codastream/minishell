/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:35:02 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/12 21:00:47 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	safe_dup2(t_data *data, int fdfrom, int fdto)
{
	int	code;

	code = dup2(fdfrom, fdto);
	handle_and_exit_if_negative(data, code, "dup error");
	pop_fd(&data->fds, fdfrom);
}

void	safe_pipe(t_data *data, int fds[2])
{
	int	code;

	code = pipe(fds);
	handle_and_exit_if_negative(data, code, "pipe error");
}

int	safe_fork(t_data *data)
{
	int	child_pid;

	child_pid = fork();
	handle_and_exit_if_negative(data, child_pid, "fork error");
	return (child_pid);
}

void	put_fd_token(t_data *data, t_token *token, int in, int out)
{
	token->out = out;
	if (PRINTFD == 1)
		printf("adding to token %s\n\tin-> %d\n\tout-> %d\n\n", \
			token->string, in, out);
	token->in = in;
	fd_push_back(&(data->fds), in);
	token->out = out;
	fd_push_back(&(data->fds), out);
	(void)data;
}
