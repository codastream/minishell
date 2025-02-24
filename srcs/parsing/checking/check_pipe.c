#include "shell.h"

void	update_command_from_string(t_data *data, t_command *command, char *string)
{
	char 		**name_with_args;

	if (command->command_args)
		ft_free_2d_char_null_ended(command->command_args);
	if (command->command_name)
		free(command->command_name);
	name_with_args = ft_split(string, ' ');
	check_alloc(data, name_with_args);
	command->command_args = name_with_args;
	command->command_name = ft_strdup(name_with_args[0]); // TODO delete and use command_args[0] when needed
	check_alloc(data, command->command_name);
}

t_command *new_command(t_data *data, char *string)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	check_alloc(data, command);
	if (string && string[0] != '\0')
	{
		update_command_from_string(data, command, string);
	}
	else
	{
		command->command_name = NULL;
		command->command_args = NULL;
	}
  command->has_invalid_redir = false;
	return (command);
}

void	add_previous_redirect_to_command(t_data *data, t_token **tokens, t_token *command_token)
{
	t_token	*current;

	current = command_token;
	while (current && current->type != T_PIPE)
	{
		current = current->prev;
		if (!current)
			return ;
		if (current->type == T_FILE && current->prev && current->prev->type == T_REDIR_IN)
		{
			command_token->command->redir_in = ft_strdup(current->string);
			check_alloc(data, command_token->command->redir_in);
			delete_token(tokens, current->prev);
			delete_token(tokens, current);
			return ; // check later in case of successive redirs
		}
		if (current->type == T_WORD && current->prev && current->prev->type == T_REDIR_HEREDOC)
		{
			command_token->command->heredoc = ft_strdup(current->string);
			check_alloc(data, command_token->command->heredoc);
			delete_token(tokens, current->prev);
			delete_token(tokens, current);
			return ; // check later in case of successive redirs
		}
	}
}

void	add_following_redirect_to_command(t_data *data, t_token **tokens, t_token *command)
{
	t_token	*current;

	current = command;
	while (current && current->type != T_PIPE)
	{
		current = current->next;
		if (!current)
			return ;
		if (current->type == T_REDIR_TRUNCATE && current->next && current->next->type == T_FILE)
		{
			command->command->redir_out_truncate = ft_strdup(current->next->string);
			check_alloc(data, command->command->redir_out_truncate);
			delete_token(tokens, current->next);
			delete_token(tokens, current);
			return ; // check later in case of successive redirs
		}
		if (current->type == T_REDIR_APPEND && current->next && current->next->type == T_FILE)
		{
			command->command->redir_out_append = ft_strdup(current->next->string);
			check_alloc(data, command->command->redir_out_append);
			delete_token(tokens, current->next);
			delete_token(tokens, current);
			return ;
		}
	}
}

void	add_command_to_token(t_data *data, t_token **tokens, t_token *token, bool is_before_pipe)
{
	t_command	*command;

	if (is_before_pipe)
		token = get_first_of_consecutive(token);
	while (token->next && token->next->type == token->type)
		merge_with_next(data, tokens, token);
	command = new_command(data, token->string);
	check_alloc(data, command);
	token->command = command;
	token->type = T_COMMAND;
	if (is_before_pipe)
		add_previous_redirect_to_command(data, tokens, token);
	else
		add_following_redirect_to_command(data, tokens, token);
}

void	add_empty_command_with_redir(t_data *data, t_token **tokens, t_token *token, bool is_before_pipe)
{
	t_token	*command_token;

	command_token = new_token(data, T_WORD, token->index, NULL);
	check_alloc(data, command_token);
	add_before(tokens, token, command_token);
	add_command_to_token(data, tokens, command_token, is_before_pipe);
}

/*
 * checks for pattern word | word
 * and assumes word are commands
 * or checks for pattern file | or | redir
 */
int	check_pipe(t_data *data, t_token **tokens, t_token *token)
{

	if (token->type != T_PIPE)
		return (EXIT_IGNORE);
	if (!token->prev || !token->next)
	{
		handle_syntax_error(data, token->string);
		return (EXIT_SYNTAX_ERROR);
	}
	if (token->prev->type == T_WORD)
		add_command_to_token(data, tokens, token->prev, true);
	else if (token->prev->type == T_FILE)
		add_empty_command_with_redir(data, tokens, token, true);
	else if (token->prev->type != T_COMMAND)
	{
		handle_syntax_error(data, token->string);
		return (EXIT_SYNTAX_ERROR);
	}
	if (token->next->type == T_WORD)
		add_command_to_token(data, tokens, token->next, false);
	else if (token->next->type != T_REDIR_TRUNCATE && token->next->type != T_REDIR_APPEND && token->next->type != T_COMMAND)
	{
		handle_syntax_error(data, token->next->string);
		return (EXIT_SYNTAX_ERROR);
	}
	return (EXIT_SUCCESS);
}
