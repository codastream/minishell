/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_init_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:33:14 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/02 17:35:34 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**init_wildcard(t_data *data, char *str)
{
	char	**wildcard;

	if (!ft_strstr(str, "*") || ft_strstr(str, "\"") || ft_strstr(str, "'") )
	{
		return (NULL);
	}
	else
	{
		wildcard = ft_calloc(wildcard_count_elem(data, str) + 1, \
			sizeof(char *));
		if (!wildcard)
			free(str);
		check_alloc(data, wildcard);
	}
	return (wildcard);
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
