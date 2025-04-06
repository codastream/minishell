/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:27:06 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**split_index(char *s, int index)
{
	int		len;
	char	**splitted;
	char	*left;
	char	*right;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (index < 0 || index >= len)
		return (NULL);
	splitted = ft_calloc(3, sizeof(char *));
	if (!splitted)
		return (NULL);
	left = ft_calloc(index + 1, sizeof(char));
	right = ft_calloc(len - index + 1, sizeof(char));
	if (!left || !right)
		return (NULL);
	ft_memcpy(left, s, index);
	left[index] = '\0';
	ft_memcpy(right, s, len - index);
	right[len - index] = '\0';
	splitted[0] = left;
	splitted[1] = right;
	splitted[2] = NULL;
	return (splitted);
}
