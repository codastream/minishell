/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:12:59 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/07 21:57:50 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_signal;

void	handle_input(t_data *data, t_redir *redir, char *eof, int fds[2])
{
	char	*input;
	char	*msg;

	msg = "%swarning: here-document delimited by end-of-file (wanted `%s')%s\n";
	input = NULL;
	while (true)
	{
		if (g_signal == 0)
			input = readline("> ");
		if (!input && g_signal == 0)
		{
			ft_printfd(2, msg, P_PINK_LIGHT, redir->string, P_NOC);
			break ;
		}
		if (g_signal != 0 || !ft_strcmp(input, eof) || !input)
			break ;
		if (!ft_strstr(redir->string, "'") && !ft_strstr(redir->string, "\""))
			expand_vars_in_heredoc(data, &input);
		ft_putstr_fd_endline(input, fds[1]);
		free(input);
	}
	free(input);
}

void	process_input(t_data *data, t_redir *redir, int fds[2])
{
	char	*eof;

	close(fds[0]);
	eof = redir->string;
	handle_quote_in_arg(data, &eof);
	handle_input(data, redir, eof, fds);
	close(fds[1]);
	free_all_data(data);
	if (g_signal + 128)
		exit(g_signal);
	exit(EXIT_SUCCESS);
}

int	init_heredoc(t_data *data, t_list *currentredir, t_redir *redir)
{
	int		fds[2];
	int		child_pid;

	(void) currentredir;
	safe_pipe(data, fds);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		setup_heredoc_signal();
		process_input(data, redir, fds);
	}
	close(fds[1]);
	waitpid(child_pid, NULL, 0);
	if (g_signal != 0)
	{
		close (fds[0]);
		return (-1);
	}
	return (fds[0]);
}
