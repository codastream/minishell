/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:45:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		total_size;
	void	*allocated;
	size_t	int_max;

	int_max = 2147483647;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (nmemb > int_max || size > int_max || nmemb * size > int_max)
		return (NULL);
	total_size = nmemb * size;
	allocated = malloc (total_size);
	if (!allocated)
		return (NULL);
	ft_bzero(allocated, total_size);
	return (allocated);
}
