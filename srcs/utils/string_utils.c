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
