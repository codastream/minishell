#include "shell.h"

t_token	*new_token(t_tokentype type, int index, char *string)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	check_malloc(token);
	token->index = index;
	token->string = string;
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
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
		*tokens = &new;
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

void	look_for_command(char *line, t_token **tokens, int *token_index)
{
	char	**command_delimiters;
	t_token	*new;
	int		found_index;
	char	*string;

	command_delimiters = ft_calloc(3, sizeof(char *));
	check_malloc(command_delimiters);
	command_delimiters[0] = " ";
	command_delimiters[1] = "|";
	command_delimiters[2] = NULL;
	found_index = ft_strstri(line, command_delimiters);
	if (found_index != -1)
	{
		string = ft_substr(line, 0, found_index);
		check_malloc(string);
		new = new_token(T_COMMAND, *token_index, string);
		check_malloc(new);
		add_token_back(tokens, new);
		line += found_index;
		*token_index++;
	}
}

void	look_for_redir(char *line, t_token **tokens, int *token_index)
{
	char	**redir_delimiters;
	t_token	*new;
	int		found_index;
	char	*string;

	redir_delimiters = ft_calloc(3, sizeof(char *));
	check_malloc(redir_delimiters);
	redir_delimiters[0] = " ";
	redir_delimiters[1] = "<";
	redir_delimiters[2] = NULL;
	found_index = ft_strstri(line, redir_delimiters);
	if (found_index != -1)
	{
		string = ft_substr(line, 0, found_index);
		check_malloc(string);
		new = new_token(T_REDIRECT, *token_index, string);
		check_malloc(new);
		add_token_back(tokens, new);
		line += found_index;
		*token_index++;
	}
}

void	tokenize(char *line)
{
	int		index;
	t_token	*tokens;

	tokens = NULL;
	index = 0;
	while(*line)
	{
		look_for_redir(line, &tokens, &index);
		look_for_command(line, &tokens, &index);
	}
	print_tokens(&tokens);
}
