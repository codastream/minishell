/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:28:48 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:33:17 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	*ft_qexit(t_queue *queue)
{
	void	*data;

	if (ft_qis_empty(queue))
		return (NULL);
	data = queue->data[queue->front];
	queue->front++;
	if (queue->front > queue->rear)
	{
		queue->front = -1;
		queue->rear = -1;
	}
	return (data);
}

void	ft_qprint_as_string(t_queue *queue)
{
	int	i;

	if (ft_qis_empty(queue))
	{
		ft_printf("[EMPTY]\n");
		return ;
	}
	i = queue->front;
	while (i < queue->rear)
	{
		ft_printf("#%d -> %s\n", i, queue->data[i]);
		i++;
	}
}
