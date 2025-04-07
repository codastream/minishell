/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_unique_values_array.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:17:26 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_unique(int value, int *uniques, int count_uniques)
{
	int	i;

	i = 0;
	while (i < count_uniques)
	{
		if (value == uniques[i])
			return (false);
		i++;
	}
	return (true);
}

bool	ft_has_unique_values_array(int *values, int size)
{
	int	*uniques;
	int	count_uniques;
	int	i;

	uniques = malloc(size * sizeof(int));
	if (!uniques)
		return (false);
	i = 0;
	count_uniques = 0;
	while (i < size)
	{
		if (is_unique(values[i], uniques, count_uniques))
			uniques[count_uniques++] = values[i];
		else
		{
			free(uniques);
			return (false);
		}
		i++;
	}
	free(uniques);
	return (true);
}
