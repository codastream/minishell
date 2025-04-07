/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:58:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_converted(int fd, char type, va_list *args)
{
	int	count;

	count = 0;
	if (type == 'c')
		count += ft_print_char_fd(fd, va_arg(*args, int));
	else if (type == 's')
		count += ft_print_str_fd(fd, va_arg(*args, const char *));
	else if (type == 'p')
		count += ft_print_address_fd(fd, va_arg(*args, intptr_t));
	else if (type == 'd' || type == 'i')
		count += ft_print_integer_fd(fd, va_arg(*args, int));
	else if (type == 'u')
		count += ft_print_unsigned_fd(fd, va_arg(*args, unsigned int));
	else if (type == 'x')
		count += ft_print_hexa_fd(fd, va_arg(*args, unsigned int), 0);
	else if (type == 'X')
		count += ft_print_hexa_fd(fd, va_arg(*args, unsigned int), 1);
	else if (type == '%')
		count += ft_print_char_fd(fd, '%');
	else
	{
		count += ft_print_char_fd(fd, '%');
		count += ft_print_char_fd(fd, type);
	}
	return (count);
}

int	ft_printfd(int fd, const char *s, ...)
{
	va_list	args;
	int		count;
	char	type;

	count = 0;
	if (!s)
		return (PRINTF_ERROR);
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			type = *(++s);
			if (type == '\0')
				return (PRINTF_ERROR);
			else
				count += write_converted(fd, type, &args);
		}
		else
			count += ft_print_char_fd(fd, *s);
		s++;
	}
	va_end(args);
	return (count);
}
