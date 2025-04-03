/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:34:18 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/31 21:35:35 by fpetit           ###   ########.fr       */
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
