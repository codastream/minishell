#include "shell.h"

char	**init_separators_for_operators(t_data *data)
{
	char		**separators;

	separators = ft_calloc(7, sizeof(char *));
	check_alloc(data, separators);
	separators[0] = " ";
	separators[1] = "|";
	separators[2] = "<<";
	separators[3] = "<";
	separators[4] = ">>";
	separators[5] = ">";
	separators[6] = NULL;
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

	delims = ft_calloc(3, sizeof(t_delimiter *));
	check_alloc(data, delims);
	delims[0] = new_delimiter(data, "\"", "\"");
	delims[1] = new_delimiter(data, "'", "'");
	delims[2] = NULL;
	return (delims);
}

static void	add_token(t_data *data, t_token **tokens, char *s, int i)
{
	t_token		*token;

	if (ft_isemptystr(s))
		return ;
	else if (s[0] == '"')
		token = new_token(data, T_LITERAL_DOUBLE, i, s);
	else if (s[0] == '\'')
		token = new_token(data, T_LITERAL_SINGLE, i, s);
	else if (!ft_strcmp(s, "|"))
		token = new_token(data, T_PIPE, i, s);
	else if (!ft_strcmp(s, "<<"))
		token = new_token(data, T_REDIR_HEREDOC, i, s);
	else if (!ft_strcmp(s, "<"))
		token = new_token(data, T_REDIR_IN, i, s);
	else if (!ft_strcmp(s, ">>"))
		token = new_token(data, T_REDIR_APPEND, i, s);
	else if (!ft_strcmp(s, ">"))
		token = new_token(data, T_REDIR_OUT, i, s);
	else
		token = new_token(data, T_WORD, i, s);
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
	// print_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	check_tokens(t_data *data, t_token **tokens)
{
	int	code;

	code = EXIT_SUCCESS;
	// printf("\n%safter tokenize%s\n", P_PINK, P_NOC);
	// print_tokens(tokens);
	// ft_put_yellow("expand in words\n");
	code = do_for_tokens(data, tokens, expand_in_words);
	if (code != EXIT_SUCCESS)
		return (code);
	// ft_put_yellow("merge word with ''\n");
	// code = do_for_tokens(data, tokens, merge_word_with_next_literal);
	// if (code != EXIT_SUCCESS)
	// 	return (code);
	// ft_put_yellow("expand in double\n");
	code = do_for_tokens(data, tokens, expand_in_double_literals);
	if (code != EXIT_SUCCESS)
		return (code);
	// ft_put_yellow("merge literal with next word\n");
	code = do_for_tokens(data, tokens, merge_literal_with_next_word);
	if (code != EXIT_SUCCESS)
		return (code);
	// ft_put_yellow("merge word with next word or literal\n");
	code = do_for_tokens(data, tokens, merge_word_with_next_word_or_literal);
	if (code != EXIT_SUCCESS)
		return (code);
	// ft_put_yellow("redir\n");
	code = do_for_tokens(data, tokens, check_redirection);
	if (code != EXIT_SUCCESS)
		return (code);
	// printf("\n%safter check redir%s\n", P_PINK, P_NOC);
	// ft_put_yellow("pipe\n");
	code = do_for_tokens(data, tokens, check_pipe);
	if (code != EXIT_SUCCESS)
		return (code);
	// ft_put_yellow("merge command with next word\n");
	code = do_for_tokens(data, tokens, merge_command_with_next_word);
	if (code != EXIT_SUCCESS)
		return (code);
	// ft_put_yellow("simple command\n");
	code = do_for_tokens(data, tokens, merge_word_with_next_words_and_make_command);
	return (code);
	// printf("\n%safter expansion%s\n", P_PINK, P_NOC);
	// print_tokens(tokens);
}

/*
 * called after syntax check
 * splits and assigns first labels (ie enums) to input parts
 */
int	tokenize(t_data *data, char *line)
{
	int		i;
	int		code;
	char	**splitted;
	char	**separators;
	t_delimiter	**delimiters;
	t_token	**tokens;

	separators = init_separators_for_operators(data);
	delimiters = init_quote_delimiters(data);
	splitted = ft_split_skip(line, separators, delimiters);
	check_alloc(data, splitted);
	tokens = ft_calloc(1, sizeof(t_token *));
	check_alloc(data, tokens);
	i = 0;
	while (splitted[i])
	{
		add_token(data, tokens, splitted[i], i);
		i++;
	}
	free(separators);
	free_delimiters(delimiters);
	ft_free_2d_char_null_ended(splitted);
	data->tokens = tokens;
	code = check_tokens(data, data->tokens);
	return (code);
}
