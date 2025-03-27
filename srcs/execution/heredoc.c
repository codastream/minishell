/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:12:59 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:16:31 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_signal = 0;

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

void	process_input(t_data *data, t_command *command, int fds[2])
{
	char	*input;
	char	*eof;

	close(fds[0]);
	eof = ft_strjoin(get_last_eofmarker(command), "\n");
	handle_quote_in_arg(data, &eof);
	check_alloc(data, eof);
	while (true)
	{
		input = readline("> ");
		input = ft_strjoinfree(input, "\n", 1);
		if (g_signal != 0 || !ft_strcmp(input, eof))
			break ;
		ft_print_str_fd(fds[1], input);
		free(input);
	}
	free(input);
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
