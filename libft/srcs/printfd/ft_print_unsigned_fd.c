/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:36:44 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned_fd(int fd, unsigned int n)
{
	char	*s;
	int		count;

	s = ft_ltoa(n);
	count = ft_print_str_fd(fd, s);
	free(s);
	return (count);
}
