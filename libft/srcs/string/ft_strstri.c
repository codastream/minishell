/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:22:24 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstri(char *str, char **searched)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (searched[j])
		{
			len = ft_strlen(searched[j]);
			if (!ft_strncmp(searched[j], &str[i], len))
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
