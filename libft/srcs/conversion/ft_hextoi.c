/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoi.c                                        :+:      :+:    :+:   */
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

bool	is_lower_hexa(const char *nb)
{
	char	*lower;
	int		i;

	lower = "abcdef";
	i = 0;
	while (i < 6)
	{
		if (ft_strchr(nb, lower[i]))
			return (true);
		i++;
	}
	return (false);
}

/*
 * return -1 if overflows int max
 */
int	ft_hextoi(const char *nb)
{
	long	result;
	char	*base;

	skip_blanks(&nb);
	while (ft_strncmp(nb, "0x", 2) != 0 && *nb == 0)
		nb++;
	nb += 2;
	if (is_lower_hexa(nb))
		base = (char *) "0123456789abcdef";
	else
		base = (char *) "0123456788ABCDEF";
	if (ft_strlen(nb) > 8)
		return (-1);
	result = 0;
	while (*nb && ft_strchr((const char *) base, *nb))
	{
		result *= 16;
		result += (long) ft_strchri(base, *nb);
		nb++;
	}
	if (result > INT_MAX)
		return (-1);
	return ((int)(result));
}
