#include "shell.h"

void	add_command_to_token(t_data *data, t_token **tokens, \
	t_token *token)
{
	t_command	*command;

	(void) tokens;
	command = new_command(data, token->string);
	check_alloc(data, command);
	token->command = command;
	token->type = T_COMMAND;
}
