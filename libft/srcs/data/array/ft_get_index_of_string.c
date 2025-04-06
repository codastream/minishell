/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_index_of_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:21:41 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * if found in s, returns the index of that string in tab
 */
int	get_index_of_matching_string(char *s, char **tab)
{
	int		i;
	size_t	len;

	i = 0;
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		if (!ft_strncmp(s, tab[i], len))
			return (i);
		i++;
	}
	return (-1);
}
