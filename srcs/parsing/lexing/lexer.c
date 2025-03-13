#include "shell.h"

static void	add_token(t_data *data, t_token **tokens, char **s, int i)
{
	t_token		*token;

	if (ft_isemptystr(s[i]))
		return ;
	else if (!ft_strcmp(s[i], "||"))
		token = new_token(data, T_AND, i, s[i]);
	else if (!ft_strcmp(s[i], "&&"))
		token = new_token(data, T_OR, i, s[i]);
	else if (!ft_strcmp(s[i], "|"))
		token = new_token(data, T_PIPE, i, s[i]);
	else if (!ft_strcmp(s[i], "<<"))
		token = new_token(data, T_REDIR_HEREDOC, i, s[i]);
	else if (!ft_strcmp(s[i], "<"))
		token = new_token(data, T_REDIR_IN, i, s[i]);
	else if (!ft_strcmp(s[i], ">>"))
		token = new_token(data, T_REDIR_APPEND, i, s[i]);
	else if (!ft_strcmp(s[i], ">"))
		token = new_token(data, T_REDIR_TRUNCATE, i, s[i]);
	else if (!ft_strcmp(s[i], "("))
		token = new_token(data, T_OPENING_PARENTHESIS, i, s[i]);
	else if (!ft_strcmp(s[i], ")"))
		token = new_token(data, T_CLOSING_PARENTHESIS, i, s[i]);
	else
		token = new_token(data, T_WORD, i, s[i]);
	add_token_back(tokens, token);
}

static int	do_for_tokens_delete(t_data *data, t_token **tokens, \
		t_token *(*f)(t_data *, t_token **, t_token *, t_token *))
{
	t_token	*current;
	t_token	*tmp;

	tmp = NULL;
	if (!tokens)
		return (EXIT_FAILURE);
	current = *tokens;
	while (current)
	{
		current = f(data, tokens, current, tmp);
	}
	if (PRINT == 1)
		print_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	do_for_tokens(t_data *data, t_token **tokens, \
		int (*f)(t_data *, t_token **, t_token *))
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
		if (current)
			current = current->next;
		else
			current = *tokens;
	}
	if (PRINT == 1)
		print_tokens(tokens);
	return (EXIT_SUCCESS);
}

static int	check_tokens(t_data *data, t_token **tokens)
{
	int	code;

	code = EXIT_SUCCESS;
	if (PRINT == 1)
		ft_put_yellow("check redir syntax\n");
	code = do_for_tokens(data, tokens, check_redirection);
	if (code != EXIT_SUCCESS)
		return (code);
	if (PRINT == 1)
		ft_put_yellow("check pipe\n");
	code = do_for_tokens(data, tokens, check_pipe);
	if (code != EXIT_SUCCESS)
		return (code);
	if (PRINT == 1)
		ft_put_yellow("merge words\n");
	code = do_for_tokens(data, tokens, update_command_from_extra_words_before_pipe);
	if (code != EXIT_SUCCESS)
		return (code);
	if (PRINT == 1)
		ft_put_yellow("add command from word\n");
	code = do_for_tokens(data, tokens, add_command_from_word);
	if (code != EXIT_SUCCESS)
		return (code);
	if (PRINT == 1)
		ft_put_yellow("add command from redirop\n");
	code = do_for_tokens_delete(data, tokens, add_command_from_redirop);
	if (code != EXIT_SUCCESS)
		return (code);
	if (PRINT == 1)
		ft_put_yellow("expand vars\n");
	code = do_for_tokens(data, tokens, expand_vars);
	if (code != EXIT_SUCCESS)
		return (code);
	if (PRINT == 1)
		ft_put_yellow("quotes\n");
	code = do_for_tokens(data, tokens, handle_quotes);
	if (code != EXIT_SUCCESS)
		return (code);
	return (code);
}

int	tokenize(t_data *data, char *line)
{
	int			i;
	int			code;
	char		**splitted;
	char		**separators;
	t_delimiter	**delimiters;

	separators = init_separators_for_operators(data);
	delimiters = init_quote_delimiters(data);
	splitted = ft_split_skip(line, separators, delimiters);
	check_alloc(data, splitted);
	data->tokens = ft_calloc(1, sizeof(t_token *));
	check_alloc(data, data->tokens);
	i = 0;
	while (splitted[i])
		add_token(data, data->tokens, splitted, i++);
	free(separators);
	free_delimiters(delimiters);
	ft_free_2d_char_null_ended(splitted);
	code = check_tokens(data, data->tokens);
	return (code);
}
