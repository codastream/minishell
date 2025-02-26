#include "parsing.h"

int	skip_quote(char *line, char type, int i)
{
	i++;
	while (line[i] != type)
		i++;
	return (i);
}

int	count_token(char *line)
{
	int	i;
	int token_count;

	i = 0;
	token_count = 1;
	if (!line[i]) // empty line
		return (0);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = skip_quote(line, line[i], i);
		if (line[i] == '|' || line[i] == '&')
			token_count += 2;
		i++;
	}
	return (token_count);
}

char	*trunk_line(char *line, int stat)
{
	static int	i = 0;
	int			j;
	int			len;
	char		*result;

	if (stat == 0)
		i = 0;
	j = i;
	if (line[i] && line[i] != '|' && line[i] != '&')
	{
		while (line[i] && (line[i] != '|' && line[i] != '&'))
		{
			if (line[i] == '\'' || line[i] == '\"')
				i = skip_quote(line, line[i], i);
			i++;
		}
	}
	else
		i++;
	len = j;
	result = ft_calloc(i - j + 1, sizeof(char));
	while (j != i)
	{
		result[j - len] = line[j];
		j++;
	}
	return (result);
}

char 	**split_skip_quotes(char *line)
{
	int	  i;
	int	  token_count;
	char  **splitted;

	token_count = count_token(line);
	splitted = ft_calloc(token_count + 1, sizeof(char *));
	i = 0;
	while (i != token_count)
	{
		splitted[i] = trunk_line(line, i);
		i++;
	}
//	free(line);
	return (splitted);
}
/*
int	main(int argc, char **argv)
{
	int	i;
	char **splitted;

	if (argc == 2)
	{
		i = 0;
		splitted = split_line(argv[1]);
		printf("%s\n\n", argv[1]);
		while (splitted[i])
		{
			printf("-> %s\n", splitted[i]);
			free(splitted[i++]);
		}
		free(splitted);
	}
}*/
