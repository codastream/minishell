/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:24:27 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str_fd(int fd, const char *s)
{
	int		count;

	count = 0;
	if (!s)
	{
		count += ft_print_str_fd(fd, "(null)");
	}
	else
	{
		if (!*s)
			return (0);
		while (s[count])
		{
			write(fd, &s[count], 1);
			count++;
		}
	}
	return (count);
}
