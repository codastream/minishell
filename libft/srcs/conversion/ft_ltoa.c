/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:56:22 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nb_len(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	reverse_buffer(char *buffer)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = ft_strlen(buffer) - 1;
	while (start < end)
	{
		temp = buffer[end];
		buffer[end] = buffer[start];
		buffer[start] = temp;
		start++;
		end--;
	}
}

static void	build_buffer(long n, char *buffer, size_t is_negative)
{
	int	i;

	i = 0;
	if (n == 0)
		buffer[i++] = '0';
	while (n > 0)
	{
		buffer[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	if (is_negative)
		buffer[i++] = '-';
	buffer[i] = '\0';
	reverse_buffer(buffer);
}

char	*ft_ltoa(long n)
{
	char		*buffer;
	size_t		is_negative;
	long long	longn;

	is_negative = 0;
	longn = (long) n;
	if (longn < 0)
	{
		is_negative = 1;
		longn *= -1;
	}
	buffer = malloc(sizeof(char) * (get_nb_len(longn) + is_negative + 1));
	if (!buffer)
		return (NULL);
	build_buffer(longn, buffer, is_negative);
	return (buffer);
}
