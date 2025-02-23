#include "shell.h"

char	**init_separators(t_data *data)
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

static void	add_token(t_data *data, t_token **tokens, char **s, int i)
{
	t_token		*token;

	if (ft_isemptystr(s[i]))
		return ;
	else if (!ft_strcmp(s[i], "|"))
		token = new_token(data, T_PIPE, i, s[i]);
	else if (!ft_strcmp(s[i], "<<"))
		token = new_token(data, T_REDIR_HEREDOC, i, s[i]);
	else if (!ft_strcmp(s[i], "<"))
		token = new_token(data, T_REDIR_IN, i, s[i]);
	else if (!ft_strcmp(s[i], ">>"))
		token = new_token(data, T_REDIR_APPEND, i, s[i]);
	else if (!ft_strcmp(s[i], ">"))
		token = new_token(data, T_REDIR_OUT, i, s[i]);
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
	return (EXIT_SUCCESS);
}

int	check_tokens(t_data *data, t_token **tokens)
{
	int	code;

	code = EXIT_SUCCESS;
	code = do_for_tokens(data, tokens, check_redirection);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_for_tokens(data, tokens, check_pipe);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_for_tokens(data, tokens, check_simple_command);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_for_tokens(data, tokens, expand_in_words);
	if (code != EXIT_SUCCESS)
		return (code);
	code = do_for_tokens(data, tokens, handle_quote);
	if (code != EXIT_SUCCESS)
		return (code);
	return(code);
	// print_tokens(tokens);
}

int	tokenize(t_data *data, char *line)
{
	int		i;
	int		code;
	char	**splitted;
	t_token	**tokens;

	i = 0;
	splitted = split_skip_quotes(line);
	tokens = ft_calloc(1, sizeof(t_token *));
	while (splitted[i])
		add_token(data, tokens, splitted, i++);
	ft_free_2d_char_null_ended(splitted);
	data->tokens = tokens;
	code = check_tokens(data, data->tokens);
	return (code);
}

/*
 * called after syntax check
 * splits and assigns first labels (ie enums) to input parts
 */
/*
int	tokenize(t_data *data, char *line)
{
	char		**separators;
	char		**splitted;
	int			i;
	t_token		**tokens;
	int			code;

	tokens = ft_calloc(1, sizeof(t_token *));
	check_alloc(data, tokens);
	separators = init_separators(data);
	check_alloc(data, separators);
	splitted = ft_split_skip(line, separators);
	check_alloc(data, splitted);
	i = 0;
	while (splitted[i])
	{
		add_token(data, tokens, splitted[i], i);
		i++;
	}
	ft_free_2d_char_null_ended(splitted);
	free(separators);
	data->tokens = tokens;
	// print_tokens(tokens);
	code = check_tokens(data, data->tokens);
	return (code);
}*/
