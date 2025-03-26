#include "shell.h"

static char	*extract_prefixed_key(t_data *data, char *s, int *i)
{
	// int		i;
	int		len;
	char	*prefixedkey;

	// i = 0;
	prefixedkey = NULL;
	if (s[*i] && s[*i] == '$' && (ft_ischarforenvvar(s[*i + 1]) || s[*i + 1] == '"' || s[*i + 1] == '?'))
	{
		// *exp_idx = i;
		len = 0;
		if (len == 0 && s[*i + 1] && s[*i + 1] == '"')
		{
			prefixedkey = ft_substr(s, *i, 1);
			check_alloc(data, prefixedkey);
			// break ;
		}
		else if (s[*i + 1] && s[*i + 1] == '?')
		{
			prefixedkey = ft_substr(s, *i, len + 2);
			check_alloc(data, prefixedkey);
			// break ;
		}
		else
		{
			while (ft_ischarforenvvar(s[*i + len + 1]))
				len++;
			prefixedkey = ft_substr(s, *i, len + 1);
			check_alloc(data, prefixedkey);
			// break ;
		}
	}
	else if (s[*i] == '$' && (s[*i + 1] == '\'' || s[*i + 1] == '\"'))
		prefixedkey = ft_strdup("$");
	return (prefixedkey);
}

static char	*extract_prefixed_key_without_quote(t_data *data, char *s, int *exp_idx, \
		char *prefixedkey)
{
	int		i;
	int		len;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && ft_ischarforenvvar(s[i + 1]))
		{
			*exp_idx = i;
			len = 0;
			if (s[i + 1] && s[i + 1] == '?')
			{
				prefixedkey = ft_substr(s, i, len + 2);
				check_alloc(data, prefixedkey);
				break ;
			}
			while (ft_ischarforenvvar(s[i + len + 1]))
				len++;
			prefixedkey = ft_substr(s, i, len + 1);
			check_alloc(data, prefixedkey);
			break ;
		}
		i++;
	}
	return (prefixedkey);
}

char	*try_replace_vars(t_data *data, char *s, int *i, int mode)
{
	char	*prefixedkey;
	char	*value;
	char	*expanded;

	prefixedkey = NULL;
	if (mode == 0)
		prefixedkey = extract_prefixed_key(data, s, i);
	else
		prefixedkey = extract_prefixed_key_without_quote(data, s, i, prefixedkey);
	if (prefixedkey && ft_strcmp(prefixedkey, "$"))
	{
		value = ft_hash_get(data->localvars, ++prefixedkey);
		// if (!ft_strcmp(value, "\""))
		// 	value = "'\"'";
		*i += ft_strlen(value);
		expanded = ft_subst_first(s, --prefixedkey, value);
		check_alloc(data, expanded);
		free(prefixedkey);
		return (expanded);
	}
	else if (prefixedkey && !ft_strcmp(prefixedkey, "$") && mode == 0)
	{
		expanded = ft_subst_first(s, "$", "");
		check_alloc(data, expanded);
		free(prefixedkey);
		return (expanded);
	}
	else
	{
		expanded = ft_strdup(s);
		*i += ft_strlen(s);
		return (expanded);
	}
}

void	toggle_quote_status(bool *in_dquote)
{
	if (*in_dquote)
		*in_dquote = false;
	else
		*in_dquote = true;
}

void	check_if_var_is_followed_by_end_of_double_quotes(char *string, int *i, bool *in_dquote)
{
	int	j;

	(void) in_dquote;
	j = *i + 1;
	if (string[j] == '?')
		j++;
	while (ft_ischarforenvvar(string[j]))
		j++;
	// if (string[j] == '"')
	// 	toggle_quote_status(in_dquote);
}

bool	next_expand(char *string, char marker, int *i, bool *in_dquote)
{
	if (!string || !string[*i])
		return (false);
	while (string[*i])
	{
		if (string[*i] == '\'' && !*in_dquote)
			skip_single_quote(string, i);
		// if (string[*i] == '\"')
		// {
		// 	toggle_quote_status(in_dquote);
		// 	(*i)++;
		while (*in_dquote && string [*i] && string[*i] != '\"')
		{
			if (string[*i] == marker)
			{
				if (string[*i + 1] && string[*i + 1] != '"' && string[*i + 1] != ' ')
				{
					check_if_var_is_followed_by_end_of_double_quotes(string, i, in_dquote);
					return (true);
				}
			}
			(*i)++;
		}
		// }
		if (string[*i] == marker && string[*i + 1])
		{
			if ((*in_dquote == false && string[*i + 1] != ' ' && string[*i + 1] != '$') || (*in_dquote && string[*i + 1] != '"'))
			{
				check_if_var_is_followed_by_end_of_double_quotes(string, i, in_dquote);
				return (true);
			}
		}
		if (string[*i])
		{
			if (string[*i] == '"')
				toggle_quote_status(in_dquote);
			if (string[*i] == '\'')
				skip_single_quote(string, i);
			(*i)++;
		}
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
	//  return (s);
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
	if (ft_isemptystr(token->command->command_args[0]) && ft_strcmp(token->command->command_name, token->command->command_args[0]))
	{
		free(token->command->command_name);
		token->command->command_name = NULL;
	}
	// expand_vars_in_redirs(data, token->command->redir_in);
	// expand_vars_in_redirs(data, token->command->redir_out_append);
	// expand_vars_in_redirs(data, token->command->redir_out_truncate);
	return (EXIT_SUCCESS);
}
