#include "shell.h"

void	add_after_splitted_on_space(t_data *data, t_token *token, int index_space)
{
	char	*string1;
	char	*string2;
	t_token	*new;

	string1 = ft_substr(token->next->string, 0, index_space);
	check_alloc(data, string1);
	new = new_token(data, T_FILE, token->index, "toto");
	check_alloc(data, new);
	free(new->string);
	new->string = string1;
	string2 = ft_substr(token->next->string, index_space + 1, \
		ft_strlen(token->next->string));
	check_alloc(data, string2);
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

void	merge_word_with_next_words(t_data *data, t_token **tokens, t_token *token)
{
	while (token->type == T_WORD && token->next && token->next->type == T_WORD)
	{
		merge_with_next(data, tokens, token);
	}
}

void	merge_word_with_next_literal(t_data *data, t_token **tokens, t_token *token)
{
	char	*trimmed;

	while (token->type == T_WORD && token->next && token->next->type == T_LITERAL_SINGLE)
	{
		trimmed = ft_strtrim(token->next->string, "'");
		check_alloc(data, trimmed);
		free(token->next->string);
		token->next->string = trimmed;
		merge_with_next(data, tokens, token);
	}
}
