/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:59:02 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/30 19:33:08 by fpetit           ###   ########.fr       */
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

	new = ft_calloc(1, sizeof(t_delimiter));
	check_alloc(data, new);
	new->opening = ft_strdup(opening);
	check_alloc(data, new->opening);
	new->closing = ft_strdup(closing);
	check_alloc(data, new->closing);
	new->level = 0;
	new->is_closed = true;
	return (new);
}

t_delimiter	**init_quote_delimiters(t_data *data)
{
	t_delimiter	**delims;

	delims = ft_calloc(3, sizeof(t_delimiter *));
	check_alloc(data, delims);
	delims[0] = new_delimiter(data, "\"", "\"");
	delims[1] = new_delimiter(data, "'", "'");
	delims[2] = NULL;
	return (delims);
}
