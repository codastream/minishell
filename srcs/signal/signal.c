/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djo <djo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:29:27 by jmassavi          #+#    #+#             */
/*   Updated: 2025/03/24 18:40:54 by djo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int g_signal;

void handle_sigint(int sig)
{
	if (sig == 2)
	{
		if (wait(0) == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			g_signal = 2;
	}
}

void  exit_heredoc(int sig)
{
  g_signal = 2;
  printf("\n");
  close(0);
  (void)sig;
}

void	exit_child(int sig)
{
	ft_printfd(2, "Quit (core dumped)\n"); //ne marche pas pour raison obscure
	signal(SIGQUIT, SIG_IGN);
	(void)sig;
}

void	setup_child_signal(void)
{
	struct sigaction	sig;
	
	sig.sa_handler = exit_child;
	sigaction(SIGQUIT, &sig, NULL);
}

void  setup_heredoc_signal(void)
{
	struct sigaction  sa;

	sa.sa_handler = exit_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);	// permet de modifier ctrl + C avec la fonction handle_sigint
	signal(SIGQUIT, SIG_IGN);		// permet d'ignorer ctrl + \ avec SIG_IGN
}
