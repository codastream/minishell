/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:37:04 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/23 19:50:57 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_double_quote(char **line)
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

char	*get_line_with_closing_quotes(char *input)
{
	char	*line;

	if (!input)
		return NULL;
	line = input;
	while (*line)
	{
		if (*line == '\"')
		{
			check_double_quote(&line);
			if (!*line)
				input = read_from_secondary(">", '"', input);
		}
		if (*line == '\'')
		{
			check_single_quote(&line);
			if (!*line)
				input = read_from_secondary(">", '\'', input);
		}
		line++;
	}
	return (input);
}
