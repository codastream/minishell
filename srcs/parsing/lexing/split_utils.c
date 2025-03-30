/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:59:02 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/31 20:43:14 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**init_separators_for_operators(t_data *data)
{
	char		**separators;

	separators = ft_calloc(10, sizeof(char *));
	check_alloc(data, separators);
	separators[1] = "|";
	separators[2] = "<<";
	separators[3] = ">>";
	separators[4] = "<";
	separators[5] = ">";
	separators[6] = NULL;
	return (separators);
}

static t_delimiter	*new_delimiter(t_data *data, char *opening, char *closing)
{
	t_delimiter	*new;

	(void) data;
	new = ft_calloc(1, sizeof(t_delimiter));
	if (!new)
		return (NULL);
	new->opening = ft_strdup(opening);
	new->closing = ft_strdup(closing);
	if (!new->opening || !new->closing)
	{
		free(new->opening);
		free(new->closing);
		free(new);
		return (NULL);
	}
	new->level = 0;
	new->is_closed = true;
	return (new);
}

t_delimiter	**init_quote_delimiters(t_data *data)
{
	t_delimiter	**delims;

	delims = ft_calloc(3, sizeof(t_delimiter *));
	if (delims)
	{
		delims[0] = new_delimiter(data, "\"", "\"");
		delims[1] = new_delimiter(data, "'", "'");
		delims[2] = NULL;
		if (!delims[0] || !delims[1])
		{
			free_delimiters(delims);
			return (NULL);
		}
	}
	return (delims);
}
