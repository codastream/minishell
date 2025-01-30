#include "shell.h"

t_command *new_command(char *string)
{
	char 		**name_with_args;
	t_command	*command;

	name_with_args = ft_split(string, ' ');
	check_alloc(name_with_args);
	command = ft_calloc(1, sizeof(t_command));
	check_alloc(command);
	command->command_args = name_with_args;
	return (command);
}

void	add_previous_redirect_to_command(t_token **tokens, t_token *command)
{
	t_token	*current;

	current = command;
	while (current && current->type != T_PIPE)
	{
		current = current->prev;
		if (!current)
			return ;
		if (current->type == T_FILE && current->prev && current->prev->type == T_REDIR_IN)
		{
			command->command->redir_in = ft_strdup(current->string);
			delete_token(tokens, current->prev);
			delete_token(tokens, current);
			return ; // check later in case of successive redirs
		}
		if (current->type == T_WORD && current->prev && current->prev->type == T_REDIR_HEREDOC)
		{
			command->command->heredoc = ft_strdup(current->string);
			delete_token(tokens, current->prev);
			delete_token(tokens, current);
			return ; // check later in case of successive redirs
		}
	}
}

void	add_following_redirect_to_command(t_token **tokens, t_token *command)
{
	t_token	*current;

	current = command;
	while (current && current->type != T_PIPE)
	{
		current = current->next;
		if (!current)
			return ;
		if (current->type == T_REDIR_OUT && current->next && current->next->type == T_FILE)
		{
			command->command->redir_out_truncate = ft_strdup(current->next->string);
			delete_token(tokens, current->next);
			delete_token(tokens, current);
			return ; // check later in case of successive redirs
		}
		if (current->type == T_REDIR_APPEND && current->next && current->next->type == T_FILE)
		{
			command->command->redir_out_append = ft_strdup(current->next->string);
			delete_token(tokens, current->next);
			delete_token(tokens, current);
			return ;
		}
	}
}

void	add_command_to_token(t_token **tokens, t_token *token, bool is_before_pipe)
{
	t_command	*command;

	if (is_before_pipe)
		token = get_first_of_consecutive(token);
	while (token->next && token->next->type == token->type)
		merge_with_next(tokens, token);
	command = new_command(token->string);
	token->command = command;
	token->type = T_COMMAND;
	if (is_before_pipe)
		add_previous_redirect_to_command(tokens, token);
	else
		add_following_redirect_to_command(tokens, token);
}

/*
 * checks for pattern word | word
 * and assumes word are commands
 */
void	check_pipe(t_token **tokens, t_token *token)
{
	if (token->type != T_PIPE)
		return ;
	if (!token->prev || !token->next)
		handle_syntax_error(token->string);
	if (token->prev->type == T_WORD)
		add_command_to_token(tokens, token->prev, true);
	else if (token->prev->type != T_FILE && token->prev->type != T_COMMAND)
		handle_syntax_error(token->string);
	if (token->next->type == T_WORD)
		add_command_to_token(tokens, token->next, false);
	else if (token->next->type != T_REDIR_OUT && token->next->type != T_REDIR_APPEND && token->next->type != T_COMMAND)
		handle_syntax_error(token->next->string);
}
