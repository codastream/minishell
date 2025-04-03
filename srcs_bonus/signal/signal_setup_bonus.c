/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:06:26 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/28 15:18:45 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_signal;

/*
 * reinitializes sigaction with memset (to prevent unexpected behavior)
 */
void	setup_child_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sig_child;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sig_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signal(void)
{
	struct sigaction	sa;

	g_signal = 0;
	sa.sa_handler = handle_sig_main;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
