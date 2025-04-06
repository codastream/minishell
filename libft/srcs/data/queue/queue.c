/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:28:48 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:33:40 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

/*
 * front is index of first elem
 * rear is index of last elem
 */
t_queue	*ft_qnew(int max_size)
{
	void	**data;
	t_queue	*queue;

	queue = ft_calloc(1, sizeof(t_queue));
	if (!queue)
		return (NULL);
	data = ft_calloc(max_size, sizeof(void *));
	if (!data)
		return (NULL);
	queue->data = data;
	queue->front = -1;
	queue->rear = -1;
	queue->items_nb = 0;
	queue->max_size = max_size;
	return (queue);
}

bool	ft_qis_empty(t_queue *queue)
{
	return (queue->items_nb == 0);
}

bool	ft_qis_full(t_queue *queue)
{
	return (queue->rear == queue->max_size - 1);
}

void	*ft_qpeek(t_queue *queue)
{
	if (ft_qis_empty(queue))
		return (NULL);
	return (queue->data[queue->front]);
}

void	ft_qadd(t_queue *queue, void *data)
{
	if (ft_qis_full(queue))
	{
		return ;
	}
	if (ft_qis_empty(queue))
	{
		queue->front = 0;
	}
	queue->rear++;
	queue->data[queue->rear] = data;
	queue->items_nb++;
}
