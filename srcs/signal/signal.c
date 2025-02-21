/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:29:27 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/23 18:03:52 by fpetit           ###   ########.fr       */
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
    {
      rl_on_new_line();
      rl_replace_line("", 0);
      printf("\n");
      g_signal = 2;
    }
	}
}

void  exit_heredoc(int sig)
{
  g_signal = 2;
  /*printf("\n");*/
  /*rl_on_new_line();*/
  /*rl_replace_line("", 0);*/
  signal(SIGINT, SIG_IGN);
  (void)sig;
}

void  setup_heredoc_signal(void)
{
  struct sigaction  sa;

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
	sigaction(SIGINT, &sa, NULL);	// permet de modifier ctrl + C avec la fonction handle_sigint
	signal(SIGQUIT, SIG_IGN);		// permet d'ignorer ctrl + \ avec SIG_IGN
}
