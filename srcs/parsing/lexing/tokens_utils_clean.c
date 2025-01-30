#include "shell.h"

void	merge_with_next(t_token **tokens, t_token *token)
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
	delete_token(tokens, token->next);
}

void	free_command(t_command *command)
{
	if (command->command_args)
		ft_free_2d_char_null_ended(command->command_args);
	if (command->command_name)
		free(command->command_name);
	if (command->command_path)
		free(command->command_path);
	free(command);
}

void	free_token(t_token *token)
{
	free(token->string);
	if (token->command)
		free_command(token->command);
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
