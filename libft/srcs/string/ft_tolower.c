/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:45:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/02 00:28:30 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
	}
	return (c);
}

char	*ft_tolowerstr(char *s)
{
	char	*lower;
	int		len;
	int		i;

	lower = ft_strdup(s);
	len = ft_strlen(lower);
	i = 0;
	while (i < len)
	{
		lower[i] = ft_tolower(lower[i]);
		i++;
	}
	return (lower);
}
