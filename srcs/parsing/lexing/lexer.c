#include "../../../includes/shell.h"

t_token	*new_token(t_tokentype type, int index, char *string)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	check_alloc(token);
	token->index = index;
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	token->string = ft_strdup(string);
	check_alloc(token->string);
	return (token);
}

t_token	*get_last(t_token **tokens)
{
	t_token	*current;

	if (!*tokens)
		return (NULL);
	current = *tokens;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

void	add_token_back(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (!tokens)
		tokens = &new;
	else
	{
		last = get_last(tokens);
		last->next = new;
		new->prev = last;
	}
}

void	print_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		printf("token #%d\n", current->index);
		printf("%s\n", current->string);
		printf("type %d\n\n", current->type);
		current = current->next;
	}
}
char **init_space_pipe_delimiters(void)
{
	char		**delimiters;

	delimiters = ft_calloc(3, sizeof(char *));
	check_alloc(delimiters);
	delimiters[0] = " ";
	delimiters[1] = "|";
	delimiters[2] = NULL;
	return (delimiters);
}

void	add_token(t_token **tokens, char *s, int i)
{
	t_token		*token;

	if (s[0] == '"')
		token = new_token(T_LITERAL_DOUBLE, i, s);
	else if (s[0] == '\'')
		token = new_token(T_LITERAL_SINGLE, i, s);
	else if (!ft_strcmp(s, "|"))
		token = new_token(T_PIPE, i, s);
	else
		token = new_token(T_WORD, i, s);
	add_token_back(tokens, token);
}

/*
 * called after syntax check
 * assigns labels (ie enums) to input parts
 */
t_token	**tokenize(char *line)
{
	char		**delimiters;
	char		**splitted;
	int			i;
	t_token 	**tokens;

	tokens = NULL;
	delimiters = init_space_pipe_delimiters();
	check_alloc(delimiters);
	splitted = ft_split_skip(line, delimiters);
	check_alloc(splitted);
	i = 0;
	while (splitted[i])
	{
		add_token(tokens, splitted[i], i);
		i++;
	}
	ft_free_2d_char_null_ended(splitted);
	free(delimiters);
	return(tokens);
}
