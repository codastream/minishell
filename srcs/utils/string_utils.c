/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:14:43 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 19:14:44 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	is_empty_line(char *line)
{
	if (!line)
		return (true);
	while (*line && ft_isemptychar(*line))
		line++;
	if (!*line)
		return (true);
	return (false);
}

bool	is_surrounded_by_pairofchar(char *s, char c)
{
	int	len;

	if (!s)
		return (false);
	len = ft_strlen(s);
	if (len == 1)
		return (false);
	if (s[0] == c && s[len - 1] == c)
		return (true);
	else
		return (false);
}

int	ft_strndup(char **var, char *cmd, int start, int end)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_calloc(end - start + 1, sizeof(char));
	if (!result)
		return (0);
	while (cmd[start] && start != end)
		result[i++] = cmd[start++];
	*var = result;
	return (1);
}
