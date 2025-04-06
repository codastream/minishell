/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:45:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:45:39 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_little;
	size_t	len_big;

	len_big = ft_strlen(big);
	len_little = ft_strlen(little);
	i = 0;
	if (!big || len == 0)
		return (NULL);
	if (len_little == 0)
		return ((char *)(big));
	while (*big && i < len)
	{
		if (i + len_little <= len_big && ft_strncmp(big, little, \
				len_little) == 0)
			return ((char *)(big));
		big++;
		i++;
	}
	return (NULL);
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	len_little;
	size_t	len_big;

	len_big = ft_strlen(big);
	len_little = ft_strlen(little);
	i = 0;
	if (!big)
		return (NULL);
	if (len_little == 0)
		return ((char *)(big));
	while (*big)
	{
		if (i + len_little <= len_big && ft_strncmp(big, little, \
				len_little) == 0)
			return ((char *)(big));
		big++;
		i++;
	}
	return (NULL);
}
