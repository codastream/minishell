#include "shell.h"

char	*try_replace_vars(t_data *data, char *s)
{
	int		i;
	int		len;
	char	*prefixedkey;
	char	*value;
	char	*expanded;

	i = 0;
	prefixedkey = NULL;
	while (s[i])
	{
		if (s[i] == '$' && ft_ischarforenvvar(s[i + 1]))
		{
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
	if (prefixedkey)
	{
//		if (++prefixedkey[0] == '?')
//			value = ft_hash_get(data->vars, LAST_RETURN_CODE);
//		else
			value = ft_hash_get(data->vars, ++prefixedkey);
//		if (!value)
//			return (ft_strdup(s));
		expanded = ft_subst(s, --prefixedkey, value);
		check_alloc(data, expanded);
		free(prefixedkey);
		return (expanded);
	}
	else
	{
		return (ft_strdup(s));
	}
}

void  skip_single_quote(char **string)
{
	char  *str;

	str = *string;
	str++;
	while (*str && *str != '\'')
		str++;
	*string = str;
}

bool	next_expand(char *string, char marker)
{
	if (!string || !*string)
		return (false);
	while (*string)
	{
		if (*string == '\'')
			skip_single_quote(&string);
		if (*string == '\"')
		{
			string++;
			while(*string != '\"')
			{
				if (*string == marker)
					return(true);
				string++;
			}
		}
		if (*string == marker)
			return(true);
		string++;
	}
	return (false);
}

int	expand_vars(t_data *data, t_token **tokens, t_token *token)
{
	char	*expanded;
	char	*s;

	(void) tokens;
	s = token->string;
	if (token->type != T_COMMAND || !s)
		return (EXIT_IGNORE);
	while (next_expand(s, '$'))
	{
		expanded = try_replace_vars(data, token->string);
		free(token->string);
		token->string = expanded;
	}
	return (EXIT_SUCCESS);
}
