/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:52:43 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/03 20:48:13 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	toggle_quote_status(bool *in_dquote)
{
	if (*in_dquote)
		*in_dquote = false;
	else
		*in_dquote = true;
}

void	check_closing_dquotes(char *string, int *i, bool *in_dquote)
{
	int	j;

	(void) in_dquote;
	j = *i + 1;
	if (string[j] == '?')
		j++;
	while (ft_ischarforenvvar(string[j]))
		j++;
}

bool	check_in_dquote(char *s, char marker, int *i, bool *in_dquote)
{
	if (s[*i] == marker)
	{
		if (s[*i + 1] && s[*i + 1] == '\'')
		{
			(*i)++;
			skip_single_quote(s, i);
			return (false);
		}
		if (s[*i + 1] && s[*i + 1] != '"' \
			&& s[*i + 1] != ' ')
		{
			check_closing_dquotes(s, i, in_dquote);
			return (true);
		}
	}
	(*i)++;
	return (false);
}

void	check_out_dquote(char *s, int *i, bool *in_dquote)
{
	if (s[*i] == '"')
		toggle_quote_status(in_dquote);
	if (s[*i] == '\'')
		skip_single_quote(s, i);
	(*i)++;
}

void	reset_arg(char **arg)
{
	free(*arg);
	*arg = NULL;
}
