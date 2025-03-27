/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:01:13 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 15:01:14 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDS_H
# define FDS_H

# include "shell.h"

void	fd_push_back(t_fds **head, int fd);
void	pop_fd(t_fds **fds, int fd);
void	pop_all_fd(t_fds **head);

#endif
