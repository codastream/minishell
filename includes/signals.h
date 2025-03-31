/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:39:41 by jmassavi          #+#    #+#             */
/*   Updated: 2025/03/28 15:50:37 by fpetit           ###   ########.fr       */
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
void	check_for_eof_and_signals(t_data *data);

#endif
