#include "shell.h"

static char	*extract_prefixed_key(t_data *data, char *s, int *exp_idx, \
		char *prefixedkey)
{
	int		i;
	int		len;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] == '$' && (ft_ischarforenvvar(s[i + 1]) || s[i + 1] == '"'))
		{
			*exp_idx = i;
			len = 0;
			if (len == 0 && s[i + 1] && s[i + 1] == '"')
			{
				prefixedkey = ft_substr(s, i, 1);
				check_alloc(data, prefixedkey);
				break ;
			}
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

char	*try_replace_vars(t_data *data, char *s, int *exp_idx)
{
	char	*prefixedkey;
	char	*value;
	char	*expanded;

	prefixedkey = NULL;
	prefixedkey = extract_prefixed_key(data, s, exp_idx, prefixedkey);
	if (prefixedkey && ft_strcmp(prefixedkey, "$"))
	{
		value = ft_hash_get(data->vars, ++prefixedkey);
		*exp_idx += ft_strlen(value);
		expanded = ft_subst_first(s, --prefixedkey, value);
		check_alloc(data, expanded);
		free(prefixedkey);
		return (expanded);
	}
	else if (!ft_strcmp(prefixedkey, "$"))
	{
		expanded = ft_subst_first(s, "$", "");
		check_alloc(data, expanded);
		free(prefixedkey);
		return (expanded);
	}
	else
	{
		expanded = ft_strdup(s);
		return (expanded);
	}
}

bool	next_expand(char *string, char marker, int *i)
{
	bool	is_opened_double_quote;
	is_opened_double_quote = false;

	if (!string || !string[*i])
		return (false);
	while (string[*i])
	{
		if (string[*i] == '\'')
			skip_single_quote(string, i);
		if (string[*i] == '\"')
		{
			if (is_opened_double_quote)
				is_opened_double_quote = true;
			else
				is_opened_double_quote = false;
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
		if (string[*i] == marker)
		{
			(*i)++;
			return (true);
		}
		if (string[*i])
			(*i)++;
	}
	return (false);
}

int	expand_vars(t_data *data, t_token **tokens, t_token *token)
{
	char	*expanded;
	char	*s;
	int		last_expanded_index;

	last_expanded_index = 0;
	(void) tokens;
	s = token->string;
	if (token->type != T_COMMAND || !s)
		return (EXIT_IGNORE);
	while (next_expand(s, '$', &last_expanded_index))
	{
		expanded = try_replace_vars(data, token->string, &last_expanded_index);
		free(token->string);
		token->string = expanded;
		s = expanded;
	}
	return (EXIT_SUCCESS);
}
