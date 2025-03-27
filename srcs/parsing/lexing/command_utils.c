#include "shell.h"

static void	update_args_and_name(t_data *data, t_command *command, char *string)
{
	t_delimiter	**delimiters;
	char		**name_with_args;
	char		**seps;

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
	command->command_name = ft_strdup(name_with_args[0]);
	check_alloc(data, command->command_name);
}

void	update_command_from_string(t_data *data, t_command *command, \
		char *string)
{
	if (command->command_args)
		ft_free_2d_char_null_ended(command->command_args);
	if (command->command_name)
		free(command->command_name);
	if (!string || ft_isemptystr(string))
	{
		command->command_args = ft_calloc(1, sizeof(char *));
		command->command_name = ft_calloc(1, sizeof(char));
		return ;
	}
	update_args_and_name(data, command, string);
}

t_command	*new_command(t_data *data, char *string)
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

t_list	**get_redir_list_from_operator(t_token *operator_token, \
		t_token *command_token)
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

// void	expand_vars_in_redirs(t_data *data, t_list *redirs)
// {
// 	char	*expanded;
// 	t_list	*current;
// 	int		index;
// 	bool	in_dquote;

// 	index = 0;
// 	in_dquote = false;
// 	current = redirs;
// 	while (current && next_expand(current->content, '$', &index, &in_dquote))
// 	{
// 		expanded = try_replace_vars(data, (char *) current->content, &index, 0);
// 		free(current->content);
// 		current->content = expanded;
// 		current = current->next;
// 	}
// }

t_list	*create_redir(t_data *data, t_token *file_token)
{
	t_list	*new;
	t_redir	*redir;
	char	*redir_file_str_expanded;
	char	*redir_file_str;
	int		index;

	index = 0;
	redir_file_str_expanded = try_replace_vars(data, (char *) file_token->string, &index, 0);
	redir_file_str = ft_subst(redir_file_str_expanded, "\"", "");
	free(redir_file_str_expanded);
	check_alloc(data, redir_file_str);
	redir = ft_calloc(1, sizeof(t_redir));
	check_alloc(data, redir);
	redir->string = redir_file_str;
	redir->type = file_token->type;
	new = ft_calloc(1, sizeof(t_list));
	check_alloc(data, new);
	new->content = redir;
	return (new);
}

void	add_redirect_file_to_command(t_data *data, t_token **tokens, \
	t_token *command_token, t_token *file_token)
{
	// t_list	*redirections;
	t_list	*redir;
	// t_list	*redir_file;

	if (PRINT == 1)
	{
		ft_put_yellow("add redirect\n");
		print_tokens(tokens);
	}
	redir = create_redir(data, file_token);
	check_alloc(data, redir);
	ft_lstadd_back(&command_token->command->redirections, redir);
	// redir_file = ft_lstnew(redir_file_str);
	// check_alloc(data, redir_file);
	// ft_lstadd_back(redir_list, redir_file);
	delete_token(tokens, file_token->prev);
	delete_token(tokens, file_token);
	if (PRINT == 1)
	{
		ft_put_yellow("after add redirect\n");
		print_tokens(tokens);
	}
}

bool	has_type_of_redir(t_command *command, t_tokentype type)
{
	t_list	*current;
	t_redir	*redir;

	current = command->redirections;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->type == type)
			return (true);
		current = current->next;
	}
	return (false);
}
