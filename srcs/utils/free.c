#include "shell.h"

void	free_tokens(t_token **tokens)
{
	t_token *current;
	t_token	*tmp;

	current = tokens[0];
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(tokens);
}
