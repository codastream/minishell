/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:36:07 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/28 14:15:03 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*extract_prefixed_key(t_data *data, char *s, int *i)
{
	int		len;
	int		sublen;
	char	*prefixedkey;

	len = 0;
	prefixedkey = NULL;
	if (s[*i] && s[*i] == '$' && (ft_ischarforenvvar(s[*i + 1]) \
		|| s[*i + 1] == '"' || s[*i + 1] == '?'))
	{
		if (len == 0 && s[*i + 1] && s[*i + 1] == '"')
			sublen = 1;
		else if (s[*i + 1] && s[*i + 1] == '?')
			sublen = 2;
		else
		{
			while (ft_ischarforenvvar(s[*i + len + 1]))
				len++;
			sublen = len + 1;
		}
		prefixedkey = ft_substr(s, *i, sublen);
		check_alloc(data, prefixedkey);
	}
	else if (s[*i] == '$' && (s[*i + 1] == '\'' || s[*i + 1] == '\"'))
		prefixedkey = ft_strdup("$");
	return (prefixedkey);
}

char	*try_replace_vars(t_data *data, char *s, int *i, int mode)
{
	char	*prefixedkey;
	char	*value;
	char	*expanded;

	prefixedkey = extract_prefixed_key(data, s, i);
	if (prefixedkey && ft_strcmp(prefixedkey, "$"))
	{
		value = ft_hash_get(data->localvars, ++prefixedkey);
		*i += ft_strlen(value);
		expanded = ft_subst_first(s, --prefixedkey, value);
	}
	else if (prefixedkey && !ft_strcmp(prefixedkey, "$") && mode == 0)
		expanded = ft_subst_first(s, "$", "");
	else
	{
		expanded = ft_strdup(s);
		*i += ft_strlen(s);
	}
	if (prefixedkey)
		free(prefixedkey);
	check_alloc(data, expanded);
	return (expanded);
}

bool	next_expand(char *s, char marker, int *i, bool *in_dquote)
{
	if (!s || !s[*i])
		return (false);
	while (s[*i])
	{
		if (s[*i] == '\'' && !*in_dquote)
			skip_single_quote(s, i);
		while (*in_dquote && s[*i] && s[*i] != '\"')
			if (check_in_dquote(s, marker, i, in_dquote))
				return (true);
		if (s[*i] == marker && s[*i + 1])
		{
			if ((*in_dquote == false && s[*i + 1] != ' ' \
				&& s[*i + 1] != '$') \
				|| (*in_dquote && s[*i + 1] != '"'))
			{
				check_closing_dquotes(s, i, in_dquote);
				return (true);
			}
		}
		if (s[*i])
			check_out_dquote(s, i, in_dquote);
	}
	return (false);
}

void	expand_vars_in_arg(t_data *data, char **arg)
{
	char	*s;
	int		last_expanded_index;
	bool	in_dquote;
	char	*expanded;

	last_expanded_index = 0;
	in_dquote = false;
	s = *arg;
	if (!ft_strstr(*arg, "$"))
		return ;
	while (s && next_expand(s, '$', &last_expanded_index, &in_dquote))
	{
		expanded = try_replace_vars(data, *arg, &last_expanded_index, 0);
		if (expanded[last_expanded_index] == '"')
		{
			toggle_quote_status(&in_dquote);
			last_expanded_index++;
		}
		free(*arg);
		*arg = expanded;
		s = expanded;
	}
	if (!ft_strcmp(*arg, ""))
		*arg = NULL;
}

int	expand_vars(t_data *data, t_token **tokens, t_token *token)
{
	int	i;

	i = 0;
	(void) tokens;
	if (token->type != T_COMMAND || !token->command->command_args)
		return (EXIT_IGNORE);
	while (token->command->command_args[i])
	{
		expand_vars_in_arg(data, &token->command->command_args[i]);
		i++;
	}
	if (ft_isemptystr(token->command->command_args[0]) \
		&& ft_strcmp(token->command->command_name, \
			token->command->command_args[0]))
	{
		free(token->command->command_name);
		token->command->command_name = NULL;
	}
	return (EXIT_SUCCESS);
}
