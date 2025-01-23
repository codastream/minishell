#include "shell.h"

void	check_heredoc(t_token *token)
{
	if (!token->next)
		handle_syntax_error("newline");
	if (token->next->type != T_WORD)
		handle_syntax_error(token->next->string);
}

void	check_redirin(t_token *token)
{
	if (!token->next)
		handle_syntax_error("newline");
	if (token->next && token->next->type == T_WORD)
		token->next->type = T_FILE;
}

void	check_redirout(t_token *token)
{
	if (!token->next)
		handle_syntax_error("newline");
	if (token->next->type != T_WORD)
		handle_syntax_error(token->next->string);
	else
		token->next->type = T_FILE;
}

void	check_append(t_token *token)
{
	if (!token->next)
		handle_syntax_error("newline");
	if (token->next->type != T_WORD)
		handle_syntax_error(token->next->string);
	else
		token->next->type = T_FILE;
}

void	check_redirection(t_token *token)
{
	if (token->type == T_WORD)
		return ;
	if (token->type == T_REDIR_HEREDOC)
		check_heredoc(token);
	if (token->type == T_REDIR_IN)
		check_redirin(token);
	if (token->type == T_REDIR_APPEND)
		check_append(token);
	if (token->type == T_REDIR_OUT)
		check_redirout(token);
}
