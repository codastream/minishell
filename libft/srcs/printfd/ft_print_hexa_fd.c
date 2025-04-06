/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:25:09 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hexa_fd(int fd, unsigned long long n, int is_upper)
{
	char	*s;
	int		count;

	if (is_upper)
		s = ft_lutoa_base(n, "0123456789ABCDEF");
	else
		s = ft_lutoa_base(n, "0123456789abcdef");
	count = ft_print_str_fd(fd, s);
	free(s);
	return (count);
}
