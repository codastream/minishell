#include "shell.h"

// void	expand_var(t_data *data, char *var)
// {
// 	int		i;
// 	char	*key;
// 	char	*result;

// 	if (!var || !*var)
// 		return ;
// 	key = *var;
// 	key++;
// 	result = ft_hash_get(data->vars, key);
// 	return (result);
// }

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
		if (s[i] == '$')
		{
			len = 0;
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
		value = ft_hash_get(data->vars, ++prefixedkey);
		if (!value)
			return (s);
		expanded = ft_subst(s, --prefixedkey, value);
		check_alloc(data, expanded);
		return (expanded);
	}
	else
	{
		return (s);
	}
}

void	expand_in_words(t_data *data, t_token **tokens, t_token *token)
{
	char	*s;
	char	*trimmed;
	char	*expanded;

	(void) tokens;
	if (token->type != T_WORD)
		return ;
	s = token->string;
	while (ft_strchri(s, '$') != -1)
	{
		expanded = try_replace_vars(data, s);
		free(s);
		s = expanded;
	}
	trimmed = ft_strtrim(s, "\"");
	check_alloc(data, trimmed);
	token->string = trimmed;
}

void	expand_in_double_literals(t_data *data, t_token **tokens, t_token *token)
{
	char	*s;
	char	*trimmed;
	char	*expanded;

	(void) tokens;
	if (token->type != T_LITERAL_DOUBLE)
		return ;
	s = token->string;
	while (ft_strchri(s, '$') != -1)
	{
		expanded = try_replace_vars(data, s);
		free(s);
		s = expanded;
	}
	trimmed = ft_strtrim(s, "\"");
	check_alloc(data, trimmed);
	token->string = trimmed;
	token->type = T_WORD;
}
