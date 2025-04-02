/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:33:44 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/02 14:46:52 by fpetit           ###   ########.fr       */
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

char	**init_strs(t_data *data, char hide, char *s, int *nb)
{
	char	**strs;

	*nb = nb_files(data, hide);
	strs = ft_calloc(*nb + 1, sizeof(char *));
	if (!strs)
		free(s);
	check_alloc(data, strs);
	return (strs);
}

void	handle_failedadd(t_data *data, char **strs, char *s, DIR *dir)
{
	ft_free_2d_char_null_ended(strs);
	free(s);
	closedir(dir);
	check_alloc(data, NULL);
}

void	free_alloc_wildcardelem(t_data *data, char **wildcard, \
		char **current_repository, char *str)
{
	free(str);
	ft_free_2d_char_null_ended(wildcard);
	ft_free_2d_char_null_ended(current_repository);
	check_alloc(data, NULL);
}
