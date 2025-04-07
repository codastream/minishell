/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:57:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/22 18:08:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

void	free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	free_splitter(t_splitter *splitter)
{
	if (!splitter)
		return ;
	free(splitter);
}

void	check_malloc(t_splitter *splitter, char **splitted, void *allocated)
{
	if (!allocated)
	{
		if (splitted)
			free_splitted(splitted);
		free_splitter(splitter);
	}
}
