/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:45:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
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

long	ft_atol(const char *nptr)
{
	int			neg;
	long long	result;

	skip_blanks(&nptr);
	neg = check_neg(&nptr);
	result = 0;
	while (ft_isdigit(*nptr))
	{
		result *= 10;
		result += (*nptr - '0');
		nptr++;
	}
	return ((long)(neg * result));
}
