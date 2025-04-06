/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:48:16 by fpetit            #+#    #+#             */
/*   Updated: 2024/11/30 17:50:33 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	swap_elems(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * pivot value is the last element
 * smaller_boundary moves till values > pivot
 * while current moves till values <= than pivot
 * so that higher values are pushed to the right
 */
static int	partition(int *tab, int from, int to)
{
	int	pivot_value;
	int	smaller_boundary;
	int	current;

	pivot_value = tab[to];
	smaller_boundary = from - 1;
	current = from;
	while (current <= to)
	{
		if (tab[current] < pivot_value)
		{
			smaller_boundary++;
			swap_elems(&tab[smaller_boundary], &tab[current]);
		}
		current++;
	}
	swap_elems(&tab[smaller_boundary + 1], &tab[to]);
	return (smaller_boundary + 1);
}

void	ft_quick_sort_tab(int *tab, int from, int to)
{
	int	pivot_index;

	if (from > to || from == to)
		return ;
	pivot_index = partition(tab, from, to);
	ft_quick_sort_tab(tab, from, pivot_index - 1);
	ft_quick_sort_tab(tab, pivot_index + 1, to);
}
