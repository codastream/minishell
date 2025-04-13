/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:36:07 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:53:04 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	next_expand_heredoc(char *s, char marker, int *i)
{
	if (!s || !s[*i])
		return (false);
	while (s[*i])
	{
		if (s[*i] == marker && s[*i + 1])
		{
			return (true);
		}
		(*i)++;
	}
	return (false);
}

void	expand_vars_in_heredoc(t_data *data, char **arg)
{
	char	*s;
	int		last_expanded_index;
	char	*expanded;

	last_expanded_index = 0;
	s = *arg;
	if (!ft_strstr(*arg, "$"))
		return ;
	while (s && next_expand_heredoc(s, '$', &last_expanded_index))
	{
		expanded = try_replace_vars(data, *arg, &last_expanded_index, HEREDOC);
		free(*arg);
		*arg = expanded;
		s = expanded;
	}
}
