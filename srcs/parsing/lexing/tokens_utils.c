#include "shell.h"

int	get_tokens_nb(t_token **tokens)
{
	int	size;
	t_token	*current;

	current = *tokens;
	if (!current)
		return (0);
	size = 1;
	while (current->next)
	{
		size++;
		current = current->next;
	}
	return (size);
}

t_token	*new_token(t_data *data, t_tokentype type, int index, char *string)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	check_alloc(data, token);
	token->index = index;
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	token->command = NULL;
	token->in = STDIN_FILENO;
	token->out = STDOUT_FILENO;
	if (string)
	{
		token->string = ft_strtrim(string, " ");
//		printf("%d -> %s\n", index, token->string);
		check_alloc(data, token->string);
	}
	else
		token->string = NULL;
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

bool	is_file(t_token *token)
{
	return (token->type == T_INFILE \
		|| token->type == T_EOF
		|| token->type == T_OUTFILE_APPEND \
		|| token->type == T_OUTFILE_TRUNCATE \
	);
}

bool	is_redir_operator(t_token *token)
{
	return (token->type == T_REDIR_HEREDOC\
		|| token->type == T_REDIR_IN
		|| token->type == T_REDIR_APPEND \
		|| token->type == T_REDIR_TRUNCATE \
	);
}
