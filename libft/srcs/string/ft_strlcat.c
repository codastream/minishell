/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:45:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_src;
	size_t	size_dest;
	size_t	remaining_size;
	size_t	i;

	size_src = ft_strlen(src);
	if (!dst && size == 0)
		return (size_src);
	size_dest = ft_strlen(dst);
	if (size < size_dest)
		return (size + size_src);
	remaining_size = size - size_dest;
	if (remaining_size > 1)
	{
		i = 0;
		while (src[i] && i < remaining_size - 1)
		{
			dst[size_dest + i] = src[i];
			++i;
		}
		dst[size_dest + i] = '\0';
	}
	return (size_src + size_dest);
}
