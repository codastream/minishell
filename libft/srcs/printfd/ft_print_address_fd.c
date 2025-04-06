/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:27:44 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:07:34 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_address_fd(int fd, intptr_t address)
{
	int		count;

	count = 0;
	if (address == 0)
	{
		count += ft_print_str_fd(fd, "(nil)");
	}
	else
	{
		count = ft_print_str_fd(fd, "0x");
		count += ft_print_hexa_fd(fd, address, 0);
	}
	return (count);
}
