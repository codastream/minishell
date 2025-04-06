/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:55:56 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:56:25 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "libft.h"

typedef struct s_queue
{
	void	**data;
	int		max_size;
	int		items_nb;
	int		front;
	int		rear;
}	t_queue;

t_queue	*ft_qnew(int max_size);
bool	ft_qis_empty(t_queue *queue);
bool	ft_qis_full(t_queue *queue);
void	*ft_qpeek(t_queue *queue);
void	ft_qadd(t_queue *queue, void *data);
void	*ft_qexit(t_queue *queue);
void	ft_qprint_as_string(t_queue *queue);

#endif
