/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:06:26 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 21:48:45 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * reinitializes sigaction with memset (to prevent unexpected behavior)
 */
void	setup_child_signal(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	sig.sa_handler = exit_child;
	sigaction(SIGQUIT, &sig, NULL);
}

void	setup_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = exit_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
