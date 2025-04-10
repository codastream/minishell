/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:11:04 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/10 17:30:10 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	skip_quote(char	*string, int *i, char quote)
{
	(*i)++;
	while (string[*i] && string[*i] != quote)
		(*i)++;
}

void	skip_single_quote(char *s, int *i)
{
	while (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
		if (s[*i] == '\'')
			(*i)++;
	}
}

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	find_index_of_space_out_of_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
			skip_quote(s, &i, s[i]);
		if (s[i] == ' ')
			return (i);
		if (s[i])
			i++;
	}
	return (-1);
}

int	is_in_quotes(char *str)
{
	if (str[0] == '"' && str[ft_strlen(str)] == '"')
		return (0);
	if (str[0] == '\'' && str[ft_strlen(str)] == '\'')
		return (0);
	return (1);
}
