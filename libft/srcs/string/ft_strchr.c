/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:45:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*s_pointer;
	int				mc;

	if (!s)
		return (NULL);
	mc = c % 256;
	s_pointer = (unsigned char *) s;
	while (*s_pointer)
	{
		if (*s_pointer == mc)
			return ((char *)(s_pointer));
		s_pointer++;
	}
	if (*s_pointer == mc)
		return ((char *)(s_pointer));
	return (NULL);
}
