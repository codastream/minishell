/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_atoistr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:27:43 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/28 13:56:58 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * returns false if
 * - has other characters than digits, +, - or space
 * - has more than one consecutive + or -
 * - has non-digit characters after the digits
 * - exceeds INT_MIN or INT_MAX
 */
bool	is_atoi_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isnumstr(&str[i]))
		return (false);
	if (i > 0 && str[i - 1] == '-')
		return (true);
	else
		return (true);
}

/*
 * imperfect for negative numb
 */
bool	is_atoll_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isnumstr(&str[i]))
		return (false);
	if (i > 0 && str[i - 1] == '-')
	{
		if (ft_strlen(&str[i - 1]) < 21 \
			&& ft_atoull(&str[i]) <= (unsigned long long) LLONG_MAX + 1)
			return (true);
	}
	else
	{
		if (ft_strlen(&str[i]) < 20 && ft_atoull(&str[i]) <= LLONG_MAX)
			return (true);
	}
	return (false);
}
