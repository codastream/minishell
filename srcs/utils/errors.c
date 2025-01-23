#include "../../includes/shell.h"

/*
 * displays an error msg on stderr with red text
 */
void	printerr(char *msg)
{
	ft_printfd(2, "%s%s%s\n", P_RED, msg, P_NOC);
}

void	printerr_syntax(char *tokenstr)
{
	ft_printfd(2, "Syntax error near unexpected token '%s'\n", tokenstr);
}

void	handle_error(char *msg)
{
	printerr(msg);
	// free previously allocated
	exit(EXIT_FAILURE);
}

void	handle_syntax_error(char *token_str)
{
	printerr_syntax(token_str);
	exit(EXIT_FAILURE);
}

void	check_alloc(void *allocated)
{
	if (!allocated)
		handle_error("memory allocation error");
}

