/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:39:41 by jmassavi          #+#    #+#             */
/*   Updated: 2025/03/27 22:20:39 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// signal
void	handle_sig_main(int sig);
void	handle_sig_heredoc(int sig);
void	handle_sig_child(int sig);

// setup
void	setup_signal(void);
void	setup_heredoc_signal(void);
void	setup_child_signal(void);

#endif
