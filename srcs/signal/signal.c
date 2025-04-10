/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:29:27 by jmassavi          #+#    #+#             */
/*   Updated: 2025/04/10 20:28:47 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_signal;

void	handle_sig_main(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = sig;
		if (wait(0) == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			printf("\n");
	}
}

void	handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = sig;
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
			g_signal = sig;
		}
	}
}

bool	check_signal_ok(t_data *data)
{
	printf("checking g signal => %d\n", g_signal);
	if (!data->line)
		handle_end_of_loop(data);
	if (g_signal == 0)
	{
		return (true);
	}
	else
	{
		update_last_return(data, 128 + g_signal);
		g_signal = 0;
		return (false);
	}
}

void	reset_g_signal(void)
{
	g_signal = 0;
}
