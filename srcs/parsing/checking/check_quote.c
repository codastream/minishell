/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:37:04 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/27 17:22:21 by fpetit           ###   ########.fr       */
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

// void	check_single_quote(char **line)
// {
// 	char	*new_line;

// 	new_line = *line;
// 	new_line++;
// 	while (*new_line && *new_line != '\'')
// 		new_line++;
// 	*line = new_line;
// }

void	check_closing_quotes(char *input)
{
	char	*line;

	if (!input)
		return ;
	line = input;
	while (*line)
	{
		if (*line == '\"')
			check_quote(&line, '\"');
		else if (*line == '\'')
			check_quote(&line, '\'');
		if (!*line)
			handle_error("invalid syntax - quotes are not properly closed");
		line++;
	}
}
