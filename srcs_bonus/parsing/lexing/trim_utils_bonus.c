/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:01:13 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:53:35 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	remove_extreme_double_quotes(t_data *data, char **s)
{
	int	first_quote_index;
	int	last_quote_index;

	first_quote_index = ft_strchri(*s, '"');
	last_quote_index = ft_strrchri(*s, '"');
	while (first_quote_index != -1 && last_quote_index != -1 \
		&& first_quote_index != last_quote_index)
	{
		remove_quotes(data, s, first_quote_index, last_quote_index);
		first_quote_index = ft_strchri(*s, '"');
		last_quote_index = ft_strrchri(*s, '"');
	}
	return (-1);
}
