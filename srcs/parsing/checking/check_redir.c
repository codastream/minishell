#include "shell.h"
void	add_command_with_heredoc(t_data *data, t_token **tokens, t_token *token)
{
	t_command	*command;
	t_token		*current;

	if (token->next->next && token->next->next->type == T_WORD)
	{
		merge_word_with_next_words(data, tokens, token->next->next);
		command = new_command(data, token->next->next->string);
		check_alloc(data, command);
		free(token->string);
		token->string = ft_strdup(token->next->next->string);
		check_alloc(data, token->string);
		delete_token(tokens, token->next->next);
	}
	else if (token->prev && token->prev->type == T_WORD)
	{
		current = get_first_of_consecutive(token->prev);
		merge_word_with_next_words(data, tokens, current);
		command = new_command(data, token->prev->string);
		check_alloc(data, command);
		free(token->string);
		token->string = ft_strdup(token->prev->string);
		check_alloc(data, token->string);
		delete_token(tokens, token->prev);
	}
	else
	{
		command = new_command(data, NULL);
		check_alloc(data, command);
	}
	command->heredoc = ft_strdup(token->next->string);
	delete_token(tokens, token->next);
	token->command = command;
	token->type = T_COMMAND;
}

void	check_heredoc(t_data *data, t_token **tokens, t_token *token)
{
	int		index_space;

	if (!token->next)
		handle_syntax_error(data, "newline");
	if (token->next->type != T_WORD)
		handle_syntax_error(data, token->next->string);
	index_space = ft_strchri(token->next->string, ' ');
	if (index_space != -1)
	{
		add_after_splitted_on_space(data, token, index_space);
	}
	token->next->type = T_EOF;
	add_command_with_heredoc(data, tokens, token);
}

void	check_redirin(t_data *data, t_token *token)
{
	int		index_space;

	if (!token->next)
		handle_syntax_error(data, "newline");
	if (token->next && token->next->type == T_WORD)
	{
		index_space = ft_strchri(token->next->string, ' ');
		if (index_space != -1)
			add_after_splitted_on_space(data, token, index_space);
		token->next->type = T_FILE;
	}
}

void	check_redirout(t_data *data, t_token *token)
{
	if (!token->next)
		handle_syntax_error(data, "newline");
	if (token->next->type != T_WORD)
		handle_syntax_error(data, token->next->string);
	else
		token->next->type = T_FILE;
}

void	check_append(t_data *data, t_token *token)
{
	if (!token->next)
		handle_syntax_error(data, "newline");
	if (token->next->type != T_WORD)
		handle_syntax_error(data, token->next->string);
	else
		token->next->type = T_FILE;
}

void	check_redirection(t_data *data, t_token **tokens, t_token *token)
{
	if (token->type == T_WORD)
		return ;
	if (token->type == T_REDIR_HEREDOC)
		check_heredoc(data, tokens, token);
	if (token->type == T_REDIR_IN)
		check_redirin(data, token);
	if (token->type == T_REDIR_APPEND)
		check_append(data, token);
	if (token->type == T_REDIR_OUT)
		check_redirout(data, token);
}
