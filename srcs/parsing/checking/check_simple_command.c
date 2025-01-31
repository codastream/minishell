#include "shell.h"

void	add_simple_command_to_token(t_token **tokens, t_token *token)
{
	t_command	*command;

	while (token->next && token->next->type == token->type)
		merge_with_next(tokens, token);
	command = new_command(token->string);
	token->command = command;
	token->type = T_COMMAND;
	add_previous_redirect_to_command(tokens, token);
	add_following_redirect_to_command(tokens, token);
}

void	check_simple_command(t_token **tokens, t_token *token)
{
	if (token->type == T_WORD)
		add_simple_command_to_token(tokens, token);
}
