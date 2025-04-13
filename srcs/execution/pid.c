/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmassavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:24:32 by jmassavi          #+#    #+#             */
/*   Updated: 2025/04/13 18:24:34 by jmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_pid	*create_pid_node(int pid)
{
	t_pid	*new_node;

	new_node = malloc(sizeof(t_pid));
	if (!new_node)
		return (NULL);
	new_node->pid = pid;
	new_node->next = NULL;
	return (new_node);
}

void	pid_push_back(t_pid **head, int pid)
{
	t_fds	*new_node;
	t_fds	*current;

	new_node = create_fds_node(pid);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next && new_node)
		current = current->next;
	current->next = new_node;
}

void	pop_front_pid(t_pid **head)
{
	t_pid	*tmp;

	if (!*head)
		return ;
	tmp = *head;
	*head = tmp->next;
	if (tmp->fd >= 3)
	{
		pop_fd(&tmp, tmp->fd);
	}
	if (tmp)
		free(tmp);
	tmp = NULL;
}


void	pop_all_pid(t_pid **head)
{
	t_pid	*tmp;

	if (!*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		pop_front_fd(&tmp);
	}
	*head = NULL;
}
