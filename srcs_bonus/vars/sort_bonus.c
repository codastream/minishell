/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:33:44 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:52:56 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	nb_files(t_data *data, char hide)
{
	int				i;
	struct dirent	*info_dir;
	DIR				*dir;
	char			*cwd;

	cwd = getpwd(data);
	if (!cwd || !cwd[0])
	{
		free(cwd);
		return (-1);
	}
	i = 0;
	dir = opendir(cwd);
	free(cwd);
	if (!dir)
		return (0);
	info_dir = readdir(dir);
	while (info_dir)
	{
		if (info_dir->d_name[0] != '.' || hide == '.')
			i++;
		info_dir = readdir(dir);
	}
	closedir(dir);
	return (i);
}

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
	if (*nb == -1)
		return (NULL);
	strs = ft_calloc(*nb + 1, sizeof(char *));
	if (!strs)
		free(s);
	check_alloc(data, strs);
	return (strs);
}
