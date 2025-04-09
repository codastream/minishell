/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:49:27 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/08 22:38:42 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	is_absolute_path(char *s)
{
	if (ft_strncmp(s, "/", 1) == 0)
		return (true);
	return (false);
}

bool	is_path(char *s)
{
	if (ft_strncmp(s, "/", 1) == 0 \
		|| ft_strncmp(s, "./", 2) == 0 \
		|| ft_strncmp(s, "../", 3) == 0 \
	)
		return (true);
	return (false);
}

char	*find_in_paths(t_data *data, char **splitted_paths, char *name)
{
	int		i;
	char	*pathname;
	char	*path_elems[2];

	i = 0;
	while (splitted_paths[i])
	{
		path_elems[0] = splitted_paths[i];
		path_elems[1] = name;
		pathname = ft_multistrjoin(2, path_elems, "/");
		if (!pathname)
			ft_free_2d_char_null_ended(splitted_paths);
		check_alloc(data, pathname);
		if (access(pathname, F_OK) == 0)
			break ;
		free(pathname);
		pathname = NULL;
		i++;
	}
	return (pathname);
}
