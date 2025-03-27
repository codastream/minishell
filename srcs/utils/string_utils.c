#include "shell.h"

void	skip_quote(char	*string, int *i, char quote)
{
	(*i)++;
	while (string[*i] && string[*i] != quote)
		(*i)++;
}

void	skip_single_quote(char *string, int *i)
{
	(*i)++;
	while (string[*i] && string[*i] != '\'')
		(*i)++;
	if (string[*i] == '\'')
		(*i)++;
}

bool	is_surrounded_by_pairofchar(char *s, char c)
{
	int	len;

	if (!s)
		return (false);
	len = ft_strlen(s);
	if (len == 1)
		return (false);
	if (s[0] == c && s[len - 1] == c)
		return (true);
	else
		return (false);
}

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	find_index_of_space_out_of_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
			skip_quote(s, &i, s[i]);
		if (s[i] == ' ')
			return (i);
		if (s[i])
			i++;
	}
	return (-1);
}
