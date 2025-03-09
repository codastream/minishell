#include "shell.h"

/*
 * checks syntax errors on the next token (inexistant, incompatible)
 */
static int	check_has_next_word(t_data *data, t_token *token)
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

static void	add_file_after_redir(t_data *data, t_token **tokens, \
		t_token *token, t_tokentype filetype)
{
	int		index_space;

	(void) tokens;
	index_space = ft_strchri(token->next->string, ' ');
	if (index_space != -1)
	{
		split_append_token(data, token, index_space, filetype);
	}
	token->next->type = filetype;
}

static int	check_redir(t_data *data, t_token **tokens, t_token *token, \
		t_tokentype filetype)
{
	int		code;

	code = check_has_next_word(data, token);
	if (code != 0)
		return (code);
	add_file_after_redir(data, tokens, token, filetype);
	return (EXIT_SUCCESS);
}

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
