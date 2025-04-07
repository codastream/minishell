/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:35:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_blanks(char **str)
{
	while (**str && ((**str >= 9 && **str <= 13) || **str == 32))
		++*str;
}

static int	compute_neg(char **str)
{
	int	neg_multiplier;

	neg_multiplier = 1;
	while (**str && (**str == '-' || **str == '+'))
	{
		if (**str == '-')
			neg_multiplier *= -1;
		++(*str);
	}
	return (neg_multiplier);
}

static int	find_index_base(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

int	ft_atoi_base(char *nbr, char *base)
{
	int	neg;
	int	result;

	skip_blanks(&nbr);
	neg = compute_neg(&nbr);
	result = 0;
	while (find_index_base(base, *nbr) != -1)
	{
		result *= ft_strlen(base);
		result += find_index_base(base, *nbr);
		nbr++;
	}
	return (result * neg);
}
