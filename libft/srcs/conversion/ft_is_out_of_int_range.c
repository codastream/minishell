/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_out_of_int_range.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:08:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:27:50 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_is_out_of_int_range(char *nb)
{
	if (ft_atol(nb) > INT_MAX || ft_atol(nb) < INT_MIN)
		return (true);
	return (false);
}
