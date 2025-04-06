/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:39:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

bool	is_valid_base(char *base)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(base) < 2)
		return (false);
	i = 0;
	while (i < ft_strlen(base) - 1)
	{
		if (base[i] == '-' || base[i] == '+' \
			|| base[i + 1] == '-' || base[i + 1] == '+')
			return (false);
		j = i + 1;
		while (j < ft_strlen(base))
		{
			if (base[i] == base[j])
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}

bool	is_valid_number_for_base(char *nbr, char *base)
{
	size_t	i;
	size_t	j;
	bool	is_valid;

	i = 0;
	is_valid = false;
	while (i < ft_strlen(nbr))
	{
		j = 0;
		while (j < ft_strlen(base))
		{
			if (nbr[i] == base[j])
				is_valid = true;
			++j;
		}
		if (is_valid == false)
			return (false);
		++i;
	}
	return (true);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long	dec_value;
	char	*buffer;
	char	*converted;

	if (!is_valid_base(base_from) || !is_valid_base(base_to))
		return (NULL);
	buffer = ft_calloc((34 + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	dec_value = (long) ft_atoi_base(nbr, base_from);
	if (dec_value < 0)
	{
		buffer[0] = '-';
		dec_value *= -1;
	}
	converted = ft_strcat(buffer, ft_lutoa_base(dec_value, base_to));
	return (converted);
}
