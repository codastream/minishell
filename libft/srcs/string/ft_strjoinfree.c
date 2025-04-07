/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:51 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:47:31 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int value)
{
	char	*result;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	result = ft_strjoin(s1, s2);
	if (!result)
		return (NULL);
	if ((value == 1 || value == 3) && s1)
		free(s1);
	if ((value == 2 || value == 3) && s2)
		free(s2);
	return (result);
}
