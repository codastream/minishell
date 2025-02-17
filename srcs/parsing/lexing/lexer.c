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

void	do_for_tokens(t_data *data, t_token **tokens, void (*f)(t_data *, t_token **, t_token *))
{
	t_token	*current;

	if (!tokens)
		return ;
	current = *tokens;
	while (current)
	{
		f(data, tokens, current);
		current = current->next;
	}
}

void	check_tokens(t_data *data, t_token **tokens)
{
	// printf("\n%safter tokenize%s\n", P_PINK, P_NOC);
	// print_tokens(tokens);
	do_for_tokens(data, tokens, expand_in_words);
	do_for_tokens(data, tokens, merge_word_with_next_literal);
	do_for_tokens(data, tokens, check_redirection);
	// printf("\n%safter check redir%s\n", P_PINK, P_NOC);
	// print_tokens(tokens);
	do_for_tokens(data, tokens, check_pipe);
	do_for_tokens(data, tokens, check_simple_command);
	do_for_tokens(data, tokens, expand_in_double_literals);
	do_for_tokens(data, tokens, merge_command_with_next_word);
	// printf("\n%safter expansion%s\n", P_PINK, P_NOC);
	// print_tokens(tokens);
}

/*
 * called after syntax check
 * splits and assigns first labels (ie enums) to input parts
 */
void	tokenize(t_data *data, char *line)
{
	char		**separators;
	char		**splitted;
	int			i;
	t_token		**tokens;

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
	check_tokens(data, tokens);
	data->tokens = tokens;
}
