/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:12:59 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/28 16:21:31 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_signal;

void	handle_input(char *eof, char *eofnoreturn, int fds[2])
{
	char	*input;
	char	*msg;

	msg = "%swarning: here-document delimited by end-of-file (wanted `%s')%s\n";
	while (true)
	{
		input = readline("> ");
		if (!input && g_signal == 0)
		{
			ft_printfd(2, msg, P_PINK_LIGHT, eofnoreturn, P_NOC);
			break ;
		}
		input = ft_strjoinfree(input, "\n", 1);
		if (g_signal != 0 || !ft_strcmp(input, eof))
			break ;
		ft_print_str_fd(fds[1], input);
		free(input);
	}
	free(input);
}

void	process_input(t_data *data, t_command *command, int fds[2])
{
	char	*eof;
	char	*eofnoreturn;

	close(fds[0]);
	eofnoreturn = get_last_eofmarker(command);
	eof = ft_strjoin(eofnoreturn, "\n");
	handle_quote_in_arg(data, &eof);
	check_alloc(data, eof);
	handle_input(eof, eofnoreturn, fds);
	free(eof);
	close(fds[1]);
	free_all_data(data);
	exit(132 - g_signal);
}

void	init_heredoc(t_data *data, t_tree **tree)
{
	int		fds[2];
	int		child_pid;

	if (!has_type_of_redir((*tree)->value->command, T_EOF))
		return ;
	safe_pipe(data, fds);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		setup_heredoc_signal();
		process_input(data, (*tree)->value->command, fds);
	}
	close(fds[1]);
	waitpid(child_pid, NULL, 0);
	if (g_signal != 0)
		close(fds[0]);
	else
		put_fd_heredoc(data, tree, fds[0], (*tree)->value->out);
}

int	heredoc_exec(t_data *data, t_tree **tree)
{
	if ((*tree)->left)
	{
		if (heredoc(data, &(*tree)->left) != 0)
			return (130);
	}
	if ((*tree)->right)
	{
		if (heredoc(data, &(*tree)->right) != 0)
			return (130);
	}
	if ((*tree)->value->type == T_COMMAND \
		&& has_type_of_redir((*tree)->value->command, T_EOF))
		init_heredoc(data, tree);
	return (g_signal);
}

int	heredoc(t_data *data, t_tree **tree)
{
	g_signal = 0;
	return (heredoc_exec(data, tree));
}
