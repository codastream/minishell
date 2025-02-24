#include "shell.h"



/*
 * checks that pipe integrates into following patterns
 * <word> OR <redir file> | <word> OR <redir file>
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
	if (token->prev->type != T_WORD && !is_file(token->prev))
		handle_syntax_error(data, token->string);
	if (token->next->type != T_WORD && !is_redir_operator(token->next))
		handle_syntax_error(data, token->next->string);
	return (EXIT_SUCCESS);
}

	// if (token->prev->type == T_WORD)
	// 	add_command_to_token(data, tokens, token->prev, true);
	// else if (token->prev->type == T_FILE)
	// 	add_empty_command_with_redir(data, tokens, token, true);
	// if (token->next->type == T_WORD)
	// 	add_command_to_token(data, tokens, token->next, false);

