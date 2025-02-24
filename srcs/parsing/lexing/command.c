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

t_list **get_redir_list_from_operator(t_token *operator_token, t_token *command_token)
{
	if (operator_token->type == T_EOF)
		return (&command_token->command->heredoc);
	else if (operator_token->type == T_REDIR_IN)
		return (&command_token->command->redir_in);
	else if (operator_token->type == T_REDIR_APPEND)
		return (&command_token->command->redir_out_append);
	else if (operator_token->type == T_REDIR_TRUNCATE)
		return (&command_token->command->redir_out_truncate);
}

void	add_redirect_file_to_command(t_data *data, t_token **tokens, t_list **redir_list, t_token *file_token)
{
	char	*redir_file_str;
	t_list	*redir_file;

	redir_file_str = ft_strdup(file_token->string);
	redir_file = ft_lstnew(redir_file_str);
	check_alloc(data, redir_file);
	ft_lstadd_back(redir_list, redir_file);
	delete_token(tokens, file_token->prev);
}

void	add_previous_redirect_to_command(t_data *data, t_token **tokens, t_token *command_token)
{
	t_token	*current;
	t_list	**redir_list;

	current = command_token;
	while (current && current->type != T_PIPE)
	{
		current = current->prev;
		if (!current)
			return ;
		if (is_file(current) && current->prev && is_redir_operator(current->prev->type))
		{
			redir_list = get_redir_list_from_operator(current->prev, command_token);
			add_redirect_file_to_command(data, tokens, redir_list, current);
			delete_token(tokens, current->prev); // delete operator token
			return ; // TODO check later in case of successive redirs
		}
	}
}

void	add_following_redirect_to_command(t_data *data, t_token **tokens, t_token *command_token)
{
	t_token	*current;
	t_list	**redir_list;

	current = command_token;
	while (current && current->type != T_PIPE)
	{
		current = current->next;
		if (!current)
			return ;
		if (is_file(current->next) && current->next && is_redir_operator(current))
		{
			redir_list = get_redir_list_from_operator(current, command_token);
			add_redirect_file_to_command(data, tokens, redir_list, current->next);
			delete_token(tokens, current); // delete operator token
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
