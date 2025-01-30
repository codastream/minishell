#include "shell.h"

void	free_command(t_command *command)
{
	if (command->command_args)
		ft_free_2d_char_null_ended(command->command_args);
	if (command->command_name)
		free(command->command_name);
	if (command->command_path)
		free(command->command_path);
	if (command->redir_in)
		free(command->redir_in);
	if (command->redir_out_append)
		free(command->redir_out_append);
	if (command->redir_out_truncate)
		free(command->redir_out_truncate);
	if (command->heredoc)
		free(command->heredoc);
	free(command);
}


void	free_token(t_token *token)
{
	if (token->command)
		free_command(token->command);
	if (token->string)
		free(token->string);
	free(token);
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*tmp;

	current = *tokens;
	while (current)
	{
		tmp = current->next;
		free_token(current);
		current = tmp;
	}
	free(tokens);
}
