/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:37:04 by jmassavi          #+#    #+#             */
/*   Updated: 2025/02/02 16:19:30 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_quote(char **line, char quote)
{
	char	*new_line;

	new_line = *line;
	new_line++;
	while (*new_line && *new_line != quote)
		new_line++;
	*line = new_line;
}

int	check_closing_quotes(t_data *data, char *input)
{
	char	*line;

	if (!input)
		return (EXIT_SYNTAX_ERROR);
	line = input;
	while (*line)
	{
		if (*line == '\"')
			check_quote(&line, '\"');
		else if (*line == '\'')
			check_quote(&line, '\'');
		if (!*line)
		{
			handle_quote_error(data);
			return (EXIT_SYNTAX_ERROR);
		}
		line++;
	}
	return (EXIT_SUCCESS);
}
