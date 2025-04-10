/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:34:18 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/10 13:58:22 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	compute_sublen(char *s, int *i, int len)
{
	int	sublen;

	while (ft_ischarforenvvar(s[*i + len + 1]))
		len++;
	sublen = len + 1;
	return (sublen);
}

void	adjust_quote_status(char *expanded, int *last_expanded_index, \
	bool *in_dquote)
{
	if (expanded[*last_expanded_index] == '"')
	{
		toggle_quote_status(in_dquote);
		*last_expanded_index += 1;
	}
}
