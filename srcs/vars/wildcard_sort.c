/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:33:44 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/02 13:59:04 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	swap(int i, int j, char **elems)
{
	char	*tmp;

	tmp = elems[i];
	elems[i] = elems[j];
	elems[j] = tmp;
}

void	sort_2dchar_null_ended(char **elems)
{
	int	n;
	int	i;
	int	cmp;

	n = ft_count_2dchar_null_ended(elems);
	while (n > 0)
	{
		i = 0;
		while (i < n - 1)
		{
			cmp = ft_strcmp_igncase(elems[i], elems[i + 1]);
			if (cmp > 0)
			{
				swap(i, i + 1, elems);
			}
			i++;
		}
		n--;
	}
}

void	add_dir_elems(t_data *data, char **strs, \
	struct dirent *info_dir, int *i)
{
	strs[*i] = ft_strdup(info_dir->d_name);
	check_alloc(data, strs[*i]);
	(*i)++;
}
