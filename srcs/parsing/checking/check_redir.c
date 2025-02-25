#include "shell.h"
// void	add_command_with_heredoc(t_data *data, t_token **tokens, t_token *token)
// {
// 	t_command	*command;
// 	t_token		*current;

// 	if (token->next->next && token->next->next->type == T_WORD)
// 	{
// 		merge_word_with_next_words(data, tokens, token->next->next);
// 		command = new_command(data, token->next->next->string);
// 		check_alloc(data, command);
// 		free(token->string);
// 		token->string = ft_strdup(token->next->next->string);
// 		check_alloc(data, token->string);
// 		delete_token(tokens, token->next->next);
// 	}
// 	else if (token->prev && token->prev->type == T_WORD)
// 	{
// 		current = get_first_of_consecutive(token->prev);
// 		merge_word_with_next_words(data, tokens, current);
// 		command = new_command(data, token->prev->string);
// 		check_alloc(data, command);
// 		free(token->string);
// 		token->string = ft_strdup(token->prev->string);
// 		check_alloc(data, token->string);
// 		delete_token(tokens, token->prev);
// 	}
// 	else
// 	{
// 		command = new_command(data, NULL);
// 		check_alloc(data, command);
// 	}
// 	command->heredoc = ft_strdup(token->next->string);
// 	delete_token(tokens, token->next);
// 	token->command = command;
// 	token->type = T_COMMAND;
// }

/*
 * checks syntax errors on the next token (inexistant, incompatible)
 */
int	check_has_next_word(t_data *data, t_token *token)
{
	if (!token->next)
	{
		handle_syntax_error(data, "newline");
		return (EXIT_SYNTAX_ERROR);
	}
	if (token->next->type != T_WORD)
	{
		handle_syntax_error(data, token->next->string);
		return (EXIT_SYNTAX_ERROR);
	}
	return (EXIT_SUCCESS);
}

void	add_file_after_redir(t_data *data, t_token **tokens, t_token *token, t_tokentype filetype)
{
	int		index_space;

	(void) tokens;
	index_space = ft_strchri(token->next->string, ' ');
	if (index_space != -1)
	{
		split_append_token(data, token, index_space, filetype);
	}
}

int	check_redir(t_data *data, t_token **tokens, t_token *token, t_tokentype filetype)
{
	int		code;

	code = check_has_next_word(data, token);
	if (code != 0)
		return (code);
	add_file_after_redir(data, tokens, token, filetype);
	return (EXIT_SUCCESS);
}

// int	check_redirin(t_data *data, t_token *token)
// {
// 	int		code;

// 	code = check_has_next_word

// 	if (token->next && token->next->type == T_WORD)
// 	{
// 		index_space = ft_strchri(token->next->string, ' ');
// 		if (index_space != -1)
// 			split_append_token(data, token, index_space);
// 		token->next->type = T_FILE;
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	check_redirout(t_data *data, t_token *token)
// {
// 	if (!token->next)
// 	{
// 		handle_syntax_error(data, "newline");
// 		return (EXIT_SYNTAX_ERROR);
// 	}
// 	if (token->next->type != T_WORD)
// 	{
// 		handle_syntax_error(data, token->next->string);
// 		return (EXIT_SYNTAX_ERROR);
// 	}
// 	else
// 		token->next->type = T_FILE;
// 	return (EXIT_SUCCESS);
// }

// int	check_append(t_data *data, t_token *token)
// {
// 	if (!token->next)
// 	{
// 		handle_syntax_error(data, "newline");
// 		return (EXIT_SYNTAX_ERROR);
// 	}
// 	if (token->next->type != T_WORD)
// 	{
// 		handle_syntax_error(data, token->next->string);
// 		return (EXIT_SYNTAX_ERROR);
// 	}
// 	else
// 		token->next->type = T_FILE;
// 	return (EXIT_SUCCESS);
// }

int	check_redirection(t_data *data, t_token **tokens, t_token *token)
{
	int	code;

	code = EXIT_IGNORE;
	if (token->type == T_REDIR_HEREDOC)
		code = check_redir(data, tokens, token, T_EOF);
	else if (token->type == T_REDIR_IN)
		code = check_redir(data, tokens, token, T_INFILE);
	else if (token->type == T_REDIR_APPEND)
		code = check_redir(data, tokens, token, T_OUTFILE_APPEND);
	else if (token->type == T_REDIR_TRUNCATE)
		code = check_redir(data, tokens, token, T_OUTFILE_TRUNCATE);
	return (code);
}
