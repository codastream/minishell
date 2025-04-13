/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djo <djo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:48:18 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/10 15:40:23 by djo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*duplicated;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	duplicated = malloc(sizeof(char) * (len + 1));
	if (!duplicated)
		return (NULL);
	ft_memcpy(duplicated, s, len);
	duplicated[len] = '\0';
	return (duplicated);
}
