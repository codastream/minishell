#include "shell.h"

void	check_heredoc(t_data *data, t_token *token)
{
	if (!token->next)
		handle_syntax_error(data, "newline");
	if (token->next->type != T_WORD)
		handle_syntax_error(data, token->next->string);
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
	(void) tokens;
	if (token->type == T_WORD)
		return ;
	if (token->type == T_REDIR_HEREDOC)
		check_heredoc(data, token);
	if (token->type == T_REDIR_IN)
		check_redirin(data, token);
	if (token->type == T_REDIR_APPEND)
		check_append(data, token);
	if (token->type == T_REDIR_OUT)
		check_redirout(data, token);
}
