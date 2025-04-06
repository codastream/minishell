/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:45:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:28:29 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_blanks(const char **str)
{
	while (**str && ((**str >= 9 && **str <= 13) || **str == 32))
		++*str;
}

static int	check_neg(const char **nptr)
{
	int	neg;

	neg = 1;
	if ((**nptr) == '+' || (**nptr) == '-')
	{
		if ((**nptr) == '-')
			neg *= -1;
		(*nptr)++;
	}
	return (neg);
}

long long	ft_atoll(const char *nptr)
{
	int					neg;
	unsigned long long	result;

	if (!nptr)
		return (0);
	skip_blanks(&nptr);
	neg = check_neg(&nptr);
	result = 0;
	while (ft_isdigit(*nptr))
	{
		result *= 10;
		result += (*nptr - '0');
		nptr++;
	}
	return ((neg * (long long) result));
}
