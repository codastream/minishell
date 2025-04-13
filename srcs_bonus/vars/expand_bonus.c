/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:36:07 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/13 16:14:12 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*extract_prefixed_key(t_data *data, char *s, int *i)
{
	int		len;
	int		sublen;
	char	*prefixedkey;

	(void) data;
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
			sublen = compute_sublen(s, i, len);
		prefixedkey = ft_substr(s, *i, sublen);
	}
	else if (s[*i] == '$' && (s[*i + 1] == '\'' || s[*i + 1] == '\"'))
		prefixedkey = ft_strdup("$");
	return (prefixedkey);
}

char	*try_replace_vars(t_data *data, char *s, int *i, t_expandmode mode)
{
	char	*prefixedkey;
	char	*value;
	char	*expanded;

	prefixedkey = extract_prefixed_key(data, s, i);
	if (prefixedkey && ft_strcmp(prefixedkey, "$"))
	{
		value = ft_hash_get(data->localvars, ++prefixedkey);
		expanded = ft_subst_first_after_i(s, --prefixedkey, value, *i);
		*i += ft_strlen(value);
	}
	else if (prefixedkey && !ft_strcmp(prefixedkey, "$") && mode == ARG)
		expanded = ft_subst_first_after_i(s, "$", "", *i);
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

void	expand_vars_in_arg(t_data *data, t_token *token, char ***arg, int i)
{
	char	*s;
	int		last_expanded_index;
	bool	in_dquote;
	bool	varindquote;
	char	*expanded;

	last_expanded_index = 0;
	varindquote = false;
	in_dquote = false;
	s = (*arg)[i];
	if (!should_expand(token, s, &varindquote))
		return ;
	while (s && next_expand(s, '$', &last_expanded_index, &in_dquote))
	{
		expanded = try_replace_vars(data, (*arg)[i], &last_expanded_index, ARG);
		adjust_quote_status(expanded, &last_expanded_index, &in_dquote);
		free((*arg)[i]);
		(*arg)[i] = expanded;
		s = expanded;
	}
	if (!varindquote)
		split_in_expand(data, token, arg, i);
}

int	expand_vars(t_data *data, t_token **tokens, t_token *token)
{
	int	i;
	int	cmd_nb;

	i = 0;
	(void) tokens;
	if (token->type != T_COMMAND || !token->command->command_args)
		return (EXIT_IGNORE);
	lst_iter_redir(data, token->command->redirections, expand_var_in_redir);
	token->command->argc = \
		ft_count_2dchar_null_ended(token->command->command_args);
	cmd_nb = token->command->argc;
	while (i < cmd_nb)
	{
		expand_vars_in_arg(data, token, &token->command->command_args, i);
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
