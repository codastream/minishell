/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isemptystr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:11:36 by fpetit            #+#    #+#             */
/*   Updated: 2024/12/02 12:46:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isemptychar(char c)
{
	return (c == ' ' || c == '\t');
}

bool	ft_isemptystr(char *s)
{
	if (ft_strlen(s) == 0)
		return (true);
	while (*s)
	{
		if (!ft_isemptychar(*s))
			return (false);
		s++;
	}
	return (true);
}
