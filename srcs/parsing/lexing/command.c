#include "shell.h"

void	update_command_from_string(t_data *data, t_command *command, char *string)
{
	char 		**name_with_args;
	char		**seps;
	t_delimiter **delimiters;

	if (command->command_args)
		ft_free_2d_char_null_ended(command->command_args);
	if (command->command_name)
		free(command->command_name);
	seps = ft_calloc(2, sizeof(char *));
	check_alloc(data, seps);
	seps[0] = " ";
	seps[1] = NULL;
	delimiters = init_quote_delimiters(data);
	name_with_args = ft_split_skip(string, seps, delimiters);
	check_alloc(data, name_with_args);
	free(seps);
	free_delimiters(delimiters);
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
	if (operator_token->type == T_REDIR_HEREDOC)
		return (&command_token->command->heredoc);
	else if (operator_token->type == T_REDIR_IN)
		return (&command_token->command->redir_in);
	else if (operator_token->type == T_REDIR_APPEND)
		return (&command_token->command->redir_out_append);
	else if (operator_token->type == T_REDIR_TRUNCATE)
		return (&command_token->command->redir_out_truncate);
	return (NULL);
}

void	add_redirect_file_to_command(t_data *data, t_token **tokens, t_list **redir_list, t_token *file_token)
{
	char	*redir_file_str;
	t_list	*redir_file;

	if (PRINT == 1)
	{
		ft_put_yellow("add redirect\n");
		print_tokens(tokens);
	}
	redir_file_str = ft_strdup(file_token->string);
	redir_file = ft_lstnew(redir_file_str);
	check_alloc(data, redir_file);
	ft_lstadd_back(redir_list, redir_file);
	delete_token(tokens, file_token->prev);
	delete_token(tokens, file_token);
}

void	add_previous_redirect_to_command(t_data *data, t_token **tokens, t_token *command_token)
{
	t_list	**redir_list;

	if (PRINT == 1)
		printf("adding previous\n");
	while (command_token && command_token->prev && command_token->prev->type != T_PIPE)
	{
		if (command_token->prev->prev && is_file(command_token->prev) && is_redir_operator(command_token->prev->prev))
		{
			redir_list = get_redir_list_from_operator(command_token->prev->prev, command_token);
			add_redirect_file_to_command(data, tokens, redir_list, command_token->prev);
		}
		print_tokens(tokens);
	}
}

void	add_following_redirect_to_command(t_data *data, t_token **tokens, t_token *command_token)
{
	t_list	**redir_list;

	while (command_token && command_token->next && command_token->next->type != T_PIPE)
	{
		if (command_token->next && is_file(command_token->next->next) && is_redir_operator(command_token->next))
		{
			redir_list = get_redir_list_from_operator(command_token->next, command_token);
			add_redirect_file_to_command(data, tokens, redir_list, command_token->next->next);
		}
	}
}

void	add_command_to_token(t_data *data, t_token **tokens, t_token *token)
{
	t_command	*command;

	(void) tokens;
	command = new_command(data, token->string);
	check_alloc(data, command);
	token->command = command;
	token->type = T_COMMAND;
}

void	add_empty_command_with_redir(t_data *data, t_token **tokens, t_token *token)
{
	t_token	*command_token;

	command_token = new_token(data, T_WORD, token->index, NULL);
	check_alloc(data, command_token);
	add_before(tokens, token, command_token);
	add_command_to_token(data, tokens, command_token);
}
int	add_command(t_data *data, t_token **tokens, t_token *token)
{
	if (token->type != T_WORD)
		return (EXIT_IGNORE);
	add_command_to_token(data, tokens, token);
	add_previous_redirect_to_command(data, tokens, token);
	add_following_redirect_to_command(data, tokens, token);
	return (EXIT_SUCCESS);
}
