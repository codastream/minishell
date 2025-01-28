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
