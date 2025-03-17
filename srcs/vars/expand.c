#include "shell.h"

static char	*extract_prefixed_key(t_data *data, char *s, int *i)
{
	// int		i;
	int		len;
	char	*prefixedkey;

	// i = 0;
	prefixedkey = NULL;
	if (s[*i] && s[*i] == '$' && (ft_ischarforenvvar(s[*i + 1]) || s[*i + 1] == '"'))
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
		value = ft_hash_get(data->vars, ++prefixedkey);
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

bool	next_expand(char *string, char marker, int *i, bool *in_dquote)
{
	if (!string || !string[*i])
		return (false);
	while (string[*i])
	{
		if (string[*i] == '\'')
			skip_single_quote(string, i);
		if (string[*i] == '\"')
		{
			toggle_quote_status(in_dquote);
			(*i)++;
			while (string [*i] && string[*i] != '\"')
			{
				if (string[*i] == marker)
				{
					if (string[*i + 1] && string[*i + 1] != '"')
						return (true);
				}
				(*i)++;
			}
		}
		if (string[*i] == marker && string[*i + 1])
		{
			if (*in_dquote == false || (*in_dquote && string[*i + 1] != '"'))
				return (true);
		}
		if (string[*i])
		{
			if (string[*i] == '"')
				toggle_quote_status(in_dquote);
			(*i)++;
		}
	}
	return (false);
}

int	expand_vars(t_data *data, t_token **tokens, t_token *token)
{
	char	*expanded;
	char	*s;
	int		last_expanded_index;
	bool	in_dquote;

	(void) tokens;
	last_expanded_index = 0;
	in_dquote = false;
	s = token->string;
	if (token->type != T_COMMAND || !s)
		return (EXIT_IGNORE);
	while (next_expand(s, '$', &last_expanded_index, &in_dquote))
	{
		expanded = try_replace_vars(data, token->string, &last_expanded_index, 0);
		free(token->string);
		token->string = expanded;
		s = expanded;
	}
	return (EXIT_SUCCESS);
}
