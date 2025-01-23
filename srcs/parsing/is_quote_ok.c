/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote_ok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:37:04 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/23 17:05:59 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_quote(char **line)
{
	char	*new_line;

	new_line = *line;
	new_line++;
	while (*new_line && *new_line != '\"')
		new_line++;
	*line = new_line;
}

void	check_single_quote(char **line)
{
	char	*new_line;

	new_line = *line;
	new_line++;
	while (*new_line && *new_line != '\'')
		new_line++;
	*line = new_line;
}

bool	is_quote_ok(char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (*line == '\"')
		{
			check_quote(&line);
			if (!*line)
				return (false);
		}
		if (*line == '\'')
		{
			check_single_quote(&line);
			if (!*line)
				return (false);
		}
		line++;
	}
	return (true);
}
