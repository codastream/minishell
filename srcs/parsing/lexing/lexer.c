#include "shell.h"

char	**init_separators(t_data *data)
{
	char		**separators;

	separators = ft_calloc(8, sizeof(char *));
	check_alloc(data, separators);
	separators[0] = "&&";
	separators[1] = "||";
	separators[2] = "|";
	separators[3] = "<<";
	separators[4] = "<";
	separators[5] = ">>";
	separators[6] = ">";
	separators[7] = NULL;
	return (separators);
}

t_delimiter	*new_delimiter(t_data *data, char *opening, char *closing)
{
	t_delimiter	*new;

	new = ft_calloc(1, sizeof(t_delimiter));
	check_alloc(data, new);
	new->opening = ft_strdup(opening);
	check_alloc(data, new->opening);
	new->closing = ft_strdup(closing);
	check_alloc(data, new->closing);
	new->level = 0;
	new->is_closed = true;
	return (new);
}
t_delimiter	**init_quote_delimiters(t_data *data)
{
	t_delimiter	**delims;
	int			nb_delims;

	nb_delims = 4;
	delims = ft_calloc(nb_delims + 1, sizeof(t_delimiter *));
	check_alloc(data, delims);
	delims[0] = new_delimiter(data, "\"", "\"");
	delims[1] = new_delimiter(data, "'", "'");
	delims[2] = new_delimiter(data, "(", ")");
	delims[3] = NULL;
	return (delims);
}

static void	add_token(t_data *data, t_token **tokens, char **s, int i)
{
	t_token		*token;

	if (ft_isemptystr(s[i]))
		return ;
	else if (!ft_strcmp(s[i], "|"))
		token = new_token(data, T_PIPE, i, s[i]);
	else
		token = new_token(data, T_WORD, i, s[i]);
	add_token_back(tokens, token);
}

int	do_for_tokens(t_data *data, t_token **tokens, int (*f)(t_data *, t_token **, t_token *))
{
	t_token	*current;
	int		code;

	if (!tokens)
		return (EXIT_FAILURE);
	current = *tokens;
	while (current)
	{
		code = f(data, tokens, current);
		if (code != EXIT_SUCCESS)
			return (code);
		current = current->next;
	}
	if (DEBUG == 1)
		print_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	check_tokens(t_data *data, t_token **tokens)
{
	int	code;

	code = EXIT_SUCCESS;
	if (DEBUG == 1)
		ft_put_yellow("check pipe\n");
	code = do_for_tokens(data, tokens, check_pipe);
	if (code != EXIT_SUCCESS)
	return (code);
	if (DEBUG == 1)
		ft_put_yellow("check redir\n");
	code = do_for_tokens(data, tokens, check_redirection);
	if (code != EXIT_SUCCESS)
	return (code);
	if (DEBUG == 1)
		ft_put_yellow("check simple command\n");
	code = do_for_tokens(data, tokens, check_simple_command);
	if (code != EXIT_SUCCESS)
	return (code);
	if (DEBUG == 1)
		ft_put_yellow("expand vars\n");
	code = do_for_tokens(data, tokens, expand_in_words);
	if (code != EXIT_SUCCESS)
	return (code);
	if (DEBUG == 1)
		ft_put_yellow("quotes\n");
	code = do_for_tokens(data, tokens, handle_quote);
	if (code != EXIT_SUCCESS)
		return (code);
	return(code);
}

int	tokenize(t_data *data, char *line)
{
	int		i;
	int		code;
	char	**splitted;
	char	**separators;
	t_delimiter	**delimiters;
	t_token	**tokens;

	separators = init_separators(data);
	delimiters = init_quote_delimiters(data);
	splitted = ft_split_skip(line, separators, delimiters);
	check_alloc(data, splitted);
	tokens = ft_calloc(1, sizeof(t_token *));
	check_alloc(data, tokens);
	i = 0;
	while (splitted[i])
		add_token(data, tokens, splitted, i++);
	free(separators);
	free_delimiters(delimiters);
	ft_free_2d_char_null_ended(splitted);
	data->tokens = tokens;
	code = check_tokens(data, data->tokens);
	return (code);
}

