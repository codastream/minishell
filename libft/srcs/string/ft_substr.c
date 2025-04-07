/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:35:07 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * returns:
 * - substring
 * - NULL if allocation fails
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*subbed;
	unsigned int	sub_len;

	if (!s)
		return (NULL);
	s_len = (unsigned int) ft_strlen(s);
	if (start >= s_len)
		return (ft_calloc(sizeof(char), 1));
	if (start + (unsigned int) len > s_len)
		sub_len = s_len - start;
	else
		sub_len = len;
	subbed = malloc(sizeof(char) * (sub_len + 1));
	if (!subbed)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		subbed[i++] = s[start++];
	}
	subbed[i] = '\0';
	return (subbed);
}
