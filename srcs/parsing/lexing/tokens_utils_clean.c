#include "shell.h"

void	merge_with_next(t_token *token)
{
	char	**tab;
	char	*newstr;

	tab = ft_calloc(2, sizeof(char *));
	check_alloc(tab);
	tab[0] = token->string;
	tab[1] = token->next->string;
	newstr = ft_strjoin(2, tab, " ");
	check_alloc(newstr);
	free(token->string);
	token->string = newstr;
	delete_token(token->next);
}

void	free_token(t_token *token)
{
	free(token->string);
	if (token->command)
		free(token->command);
}

void	delete_token(t_token *token)
{
	t_token	*tokens;

	tokens = token;
	while (tokens->prev)
		tokens = tokens->prev;
	if (token->prev)
		token->prev->next = token->next;
	else
		tokens = token->next;
	if (token->next && token->prev)
		token->next->prev = token->prev;
	free_token(token);
}
