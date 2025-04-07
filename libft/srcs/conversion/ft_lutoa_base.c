/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:41:43 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * initialize with max length
 * = UNSIGNED LONG LONG MAX in binary needs 63 + 1 bits
 */
char	*ft_lutoa_base(unsigned long long n, char *base)
{
	char				*buffer;
	char				*temp;
	unsigned long long	len_base;

	len_base = (unsigned long long) ft_strlen(base);
	buffer = ft_calloc((63 + 1), sizeof(char));
	if (n >= len_base)
	{
		temp = ft_lutoa_base(n / len_base, base);
		buffer = ft_strcat(buffer, temp);
		free(temp);
	}
	buffer[ft_strlen(buffer)] = base[n % len_base];
	buffer[ft_strlen(buffer)] = '\0';
	return (buffer);
}
