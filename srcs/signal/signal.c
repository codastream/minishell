/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:29:27 by jmassavi          #+#    #+#             */
/*   Updated: 2025/03/27 22:23:33 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_signal;

void	handle_sig_main(int sig)
{
	if (sig == SIGINT)
	{
		if (wait(0) == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			g_signal = 128 + sig;
		}
	}
}

void	handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 2;
		printf("\n");
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
		}
	}
}
