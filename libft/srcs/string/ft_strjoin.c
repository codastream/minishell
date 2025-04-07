/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:48:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strslen(char **tab, int size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < size)
	{
		len += ft_strlen(tab[i]);
		i++;
	}
	return (len);
}

char	*ft_multistrjoin(int size, char **strs, char *sep)
{
	char	*joined;
	int		i;
	size_t	len;

	len = 0;
	if (size > 0)
		len = ft_strslen(strs, size) + (size -1) * ft_strlen(sep);
	joined = ft_calloc((len + 1), sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < size)
	{
		joined = ft_strcat(joined, strs[i]);
		if (i < size - 1)
			joined = ft_strcat(joined, sep);
		i++;
	}
	return (joined);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	unsigned int	i;

	if (!s1 || !s2)
		return (NULL);
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)])
	{
		result[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	result[i] = '\0';
	return (result);
}
