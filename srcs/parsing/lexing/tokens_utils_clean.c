#include "shell.h"

void	merge_with_next(t_data *data, t_token **tokens, t_token *token)
{
	char	**tab;
	char	*newstr;

	tab = ft_calloc(3, sizeof(char *));
	check_alloc(data, tab);
	tab[0] = token->string;
	tab[1] = ft_strdup(token->next->string);
	check_alloc(data, tab[1]);
	tab[2] = NULL;
	newstr = ft_strjoin(2, tab, " ");
	check_alloc(data, newstr);
	ft_free_2d_char_null_ended(tab);
	delete_token(tokens, token->next);
	token->string = newstr;
}

void	delete_token(t_token **tokens, t_token *token)
{
	if (token->prev)
		token->prev->next = token->next;
	else
	{
		*tokens = token->next;
		(*tokens)->prev = NULL;
	}
	if (token->next && token->prev)
		token->next->prev = token->prev;
	free_token(token);
}
