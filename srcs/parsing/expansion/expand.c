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
		free(prefixedkey);
		return (expanded);
	}
	else
	{
		return (s);
	}
}

int	expand_in_words(t_data *data, t_token **tokens, t_token *token)
{
	char	*expanded;

	(void) tokens;
	if (token->type != T_WORD)
		return (EXIT_IGNORE);
	while (ft_strchri(token->string, '$') != -1)
	{
		expanded = try_replace_vars(data, token->string);
		free(token->string);
		token->string = expanded;
	}
	return (EXIT_SUCCESS);
}

int	expand_in_double_literals(t_data *data, t_token **tokens, t_token *token)
{
	char	*trimmed;
	char	*expanded;

	(void) tokens;
	if (token->type != T_LITERAL_DOUBLE)
		return (EXIT_IGNORE);
	while (ft_strchri(token->string, '$') != -1)
	{
		expanded = try_replace_vars(data, token->string);
		free(token->string);
		token->string = expanded;
	}
	trimmed = ft_strtrim(token->string, "\"");
	check_alloc(data, trimmed);
	free(token->string);
	token->string = trimmed;
	return (EXIT_SUCCESS);
}
