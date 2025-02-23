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

void  skip_single_quote(char **string)
{
	char  *str;

	str = *string;
	str++;
	while (*str && *str != '\'')
		str++;
	*string = str;
}

int next_expend(char *string, char chr)
{
	if (!*string)
		return (-1);
	while (*string)
	{
		if (*string == '\'')
			skip_single_quote(&string);
		if (*string == '\"')
		{
			string++;
			while(*string == '\"')
			{
				if (*string == chr)
					return(0);
				string++;
			}
		}
		if (*string == chr)
			return(0);
		string++;
	}
	return (-1);
}

int	expand_in_words(t_data *data, t_token **tokens, t_token *token)
{
	char	*expanded;

	(void) tokens;
	if (token->type != T_WORD)
		return (EXIT_IGNORE);
	while (next_expend(token->string, '$') != -1)
	{
		expanded = try_replace_vars(data, token->string);
		free(token->string);
		token->string = expanded;
	}
	return (EXIT_SUCCESS);
}

void  trime_quote(char **str, int first_quote, int second_quote)
{
	int	  i;
	int	  j;
	char  *trimmed;

	i = 0;
	j = 0;
	trimmed = ft_calloc(ft_strlen(*str) - 1, sizeof(char));
	if (!trimmed)
		return ;
	while ((*str)[i])
	{
		if (i != first_quote && i != second_quote)
		{
			trimmed[j] = (*str)[i];
			j++;
		}
		i++;
	}
	free(*str);
	*str = trimmed;
}

int  handle_double_quote(t_data *data, char **trimmed, int i)
{
	int	  j;

	j = i;
	if ((*trimmed)[i])
	{
		i++;
		while ((*trimmed)[i] && (*trimmed)[i] != '\"')
			i++;
		if ((*trimmed)[i])
		{
			trime_quote(trimmed, j, i);
			i = i - 2;
		}
		check_alloc(data, (*trimmed));
	}
	return (i);
}

int  handle_single_quote(t_data *data, char **trimmed, int i)
{
	int	  j;

	j = i;
	if ((*trimmed)[i])
	{
		i++;
		while ((*trimmed)[i] && (*trimmed)[i] != '\'')
			i++;
		if ((*trimmed)[i])
		{
			trime_quote(trimmed, j, i);
			i = i - 2;
		}
		check_alloc(data, (*trimmed));
	}
	return (i);
}

int	handle_quote(t_data *data, t_token **tokens, t_token *token)
{
	int	  i;
	char  *trimmed;

	trimmed = token->string;
	i = 0;
	(void)tokens;
	while (trimmed[i])
	{
		if (trimmed[i] == '\"')
			i = handle_double_quote(data, &trimmed, i);
		if (trimmed[i] == '\'')
			i = handle_single_quote(data, &trimmed, i);
		i++;
	}
	token->string = trimmed;
	return (EXIT_SUCCESS);
}

/*int	expand_in_double_literals(t_data *data, t_token **tokens, t_token *token)*/
/*{*/
/*	char	*trimmed;*/
/*	char	*expanded;*/
/**/
/*	(void) tokens;*/
/*	while (ft_strchri(token->string, '$') != -1)*/
/*	{*/
/*		expanded = try_replace_vars(data, token->string);*/
/*		free(token->string);*/
/*		token->string = expanded;*/
/*	}*/
/*	trimmed = ft_strtrim(token->string, "\"");*/
/*	check_alloc(data, trimmed);*/
/*	free(token->string);*/
/*	token->string = trimmed;*/
/*	token->type = T_WORD;*/
/*	return (EXIT_SUCCESS);*/
/*}*/
