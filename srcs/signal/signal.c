/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:29:27 by jmassavi          #+#    #+#             */
/*   Updated: 2025/04/01 15:09:43 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_signal;

void	handle_sig_main(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 128 + sig;
		if (wait(0) == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			printf("\n");
		printf("la\n");
	}
}

void	handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 128 + sig;
		close(0);
	}
}

void	handle_sig_child(int sig)
{
	int		result;

	if (sig == SIGQUIT)
	{
		result = wait(0);
		if (result != -1)
		{
			ft_printfd(2, "Quit\n");
			setup_signal();
			g_signal = 128 + sig;
		}
	}
}

void	check_for_eof_and_signals(t_data *data)
{
	if (g_signal != 0)
		update_last_return(data, g_signal);
	if (!data->line)
		handle_end_of_loop(data);
	g_signal = 0;
}
