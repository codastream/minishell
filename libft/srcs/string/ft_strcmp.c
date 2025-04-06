/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:45:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/02 14:03:13 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1)
		return ((unsigned char) *s2);
	if (!s2)
		return ((unsigned char) *s1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	ft_strcmp_igncase(const char *s1, const char *s2)
{
	size_t	i;
	char	*l1;
	char	*l2;
	int		result;

	if (!s1)
		return ((unsigned char) *s2);
	if (!s2)
		return ((unsigned char) *s1);
	l1 = ft_tolowerstr((char *)s1);
	l2 = ft_tolowerstr((char *)s2);
	i = 0;
	while (l1[i] && l2[i] && (l1[i] == l2[i]))
		i++;
	result = (unsigned char)(l1[i]) - \
		(unsigned char)(l2[i]);
	free(l1);
	free(l2);
	return (result);
}
