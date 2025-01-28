#include "shell.h"

void	add_after_splitted_on_space(t_token *token, int index_space)
{
	char	*string1;
	char	*string2;
	t_token	*new;

	string1 = ft_substr(token->next->string, 0, index_space);
	check_alloc(string1);
	new = new_token(T_FILE, token->index, string1);
	check_alloc(new);
	string2 = ft_substr(token->next->string, index_space + 1, \
		ft_strlen(token->next->string));
	check_alloc(string2);
	free(token->next->string);
	token->next->string = string2;
	add_after(token, new);
}

void	merge_single_literal_with_preceding_word(t_token *token)
{
	if (token->type == T_WORD && token->next && token->next->type == T_LITERAL_SINGLE)
	{
		merge_with_next(token);
	}
}
