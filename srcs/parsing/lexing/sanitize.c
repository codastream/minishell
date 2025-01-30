#include "shell.h"

void	add_after_splitted_on_space(t_token *token, int index_space)
{
	char	*string1;
	char	*string2;
	t_token	*new;

	string1 = ft_substr(token->next->string, 0, index_space);
	check_alloc(string1);
	new = new_token(T_FILE, token->index, "toto");
	check_alloc(new);
	free(new->string);
	new->string = string1;
	string2 = ft_substr(token->next->string, index_space + 1, \
		ft_strlen(token->next->string));
	check_alloc(string2);
	free(token->next->string);
	token->next->string = string2;
	add_after(token, new);
}

t_token	*get_first_of_consecutive(t_token *token)
{
	t_token	*current;

	current = token;
	while (current->prev && current->prev->type == current->type)
	{
		current = current->prev;
	}
	return (current);
}

void	merge_word_with_next_words(t_token **tokens, t_token *token)
{
	while (token->type == T_WORD && token->next && token->next->type == T_WORD)
	{
		merge_with_next(tokens, token);
	}
}

void	merge_word_with_next_literal(t_token **tokens, t_token *token)
{
	char	*trimmed;

	while (token->type == T_WORD && token->next && token->next->type == T_LITERAL_SINGLE)
	{
		trimmed = ft_strtrim(token->next->string, "'");
		free(token->next->string);
		token->next->string = trimmed;
		merge_with_next(tokens, token);
	}
}
