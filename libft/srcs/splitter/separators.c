/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:09:00 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:37:34 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

void	add_sep(t_splitter *splitter, char *sep, size_t *i, char **splitted)
{
	int		e;
	size_t	len_sep;

	len_sep = ft_strlen(sep);
	if (!ft_isemptystr(sep))
	{
		e = ft_count_2dchar_null_ended(splitted);
		splitted[e] = ft_strdup(sep);
		check_malloc(splitter, splitted, splitted[e]);
	}
	*i += len_sep;
}

void	count_sep(char *sep, size_t *i, int *count)
{
	size_t	len;

	if (!ft_isemptystr(sep))
		*count += 1;
	len = ft_strlen(sep);
	*i += len;
}

char	*get_sep_not_space(char *s, char **seps)
{
	char	*sep;

	sep = get_sep(s, seps);
	if (!ft_strcmp(sep, " "))
		return (NULL);
	else
		return (sep);
}

char	*get_sep(char *s, char **seps)
{
	int		j;
	size_t	len_sep;

	j = 0;
	while (seps[j])
	{
		len_sep = ft_strlen(seps[j]);
		if (!ft_strncmp(s, seps[j], len_sep))
			return (seps[j]);
		j++;
	}
	return (NULL);
}
