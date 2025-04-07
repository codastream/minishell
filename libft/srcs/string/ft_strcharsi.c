/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcharsi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:12:22 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * returns index of first character among searched in str
 * returns -1 if no character of searched is found in str
 */
int	ft_strcharsi(char *str, char *searched)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchri(searched, str[i]) == -1)
			i++;
		else
			return (i);
	}
	return (-1);
}
