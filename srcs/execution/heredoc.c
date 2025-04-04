/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:12:59 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/31 20:48:20 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_signal;

void	handle_input(char *eof, char *eofnoreturn, int fds[2])
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
			ft_printfd(2, msg, P_PINK_LIGHT, eofnoreturn, P_NOC);
			break ;
		}
		input = ft_strjoinfree(input, "\n", 1);
		if (g_signal != 0 || !ft_strcmp(input, eof) || !input)
			break ;
		ft_print_str_fd(fds[1], input);
		free(input);
	}
	free(input);
}

void	process_input(t_data *data, t_redir *redir, int fds[2])
{
	char	*eof;
	char	*eofnoreturn;

	close(fds[0]);
	eofnoreturn = redir->string;
	eof = ft_strjoin(eofnoreturn, "\n");
	if (!eof)
		close(fds[1]);
	check_alloc(data, eof);
	handle_quote_in_arg(data, &eof);
	handle_input(eof, eofnoreturn, fds);
	free(eof);
	close(fds[1]);
	free_all_data(data);
	if (g_signal != 0)
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
