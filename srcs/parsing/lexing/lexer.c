#include "shell.h"

t_token	*new_token(t_tokentype type, int index, char *string)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	check_alloc(token);
	token->index = index;
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	token->command = NULL;
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

	if (!*tokens)
		*tokens = new;
	else
	{
		last = get_last(tokens);
		last->next = new;
		new->prev = last;
	}
}

char **init_separators(void)
{
	char		**separators;

	separators = ft_calloc(7, sizeof(char *));
	check_alloc(separators);
	separators[0] = " ";
	separators[1] = "|";
	separators[2] = "<<";
	separators[3] = "<";
	separators[4] = ">>";
	separators[5] = ">";
	separators[6] = NULL;
	return (separators);
}

void	add_before(t_token **tokens, t_token *current, t_token *new)
{
	t_token	*tmp;

	if (!tokens || !current || !new)
		return ;
	if (current->prev)
	{
		tmp = current->prev;
		new->next = current;
		current->prev = new;
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*tokens = new;
		current->prev = new;
		new->next = current;
	}
}

void	add_after(t_token *current, t_token *new)
{
	t_token	*tmp;
	if (!current || !new)
		return ;
	if (current->next)
	{
		tmp = current->next;
		current->next = new;
		new->prev = current;
		new->next = tmp;
		tmp->prev = new;
	}
	else
	{
		current->next = new;
		new->prev = current;
	}
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
	else if (!ft_strcmp(s, "<<"))
		token = new_token(T_REDIR_HEREDOC, i, s);
	else if (!ft_strcmp(s, "<"))
		token = new_token(T_REDIR_IN, i, s);
	else if (!ft_strcmp(s, ">>"))
		token = new_token(T_REDIR_APPEND, i, s);
	else if (!ft_strcmp(s, ">"))
		token = new_token(T_REDIR_OUT, i, s);
	else
		token = new_token(T_WORD, i, s);
	add_token_back(tokens, token);
}

void	do_for_tokens(t_token **tokens, void (*f)(t_token *))
{
	t_token	*current;

	if (!tokens)
		return ;
	current = *tokens;
	while (current)
	{
		f(current);
		current = current->next;
	}
}

/*
 * called after syntax check
 * splits and assigns first labels (ie enums) to input parts
 */
t_token	**tokenize(char *line)
{
	char		**separators;
	char		**splitted;
	int			i;
	t_token 	**tokens;

	tokens = ft_calloc(1, sizeof(t_token *));
	check_alloc(tokens);
	separators = init_separators();
	check_alloc(separators);
	splitted = ft_split_skip(line, separators);
	check_alloc(splitted);
	i = 0;
	while (splitted[i])
	{
		add_token(tokens, splitted[i], i);
		i++;
	}
	ft_free_2d_char_null_ended(splitted);
	free(separators);
	return(tokens);
}
