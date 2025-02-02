#include "shell.h"

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

void	handle_error(t_data *data, char *msg)
{
	printerr(msg);
	free_data(data);
	exit(EXIT_FAILURE);
}

void	handle_code(t_data *data, int code, char *msg)
{
	if (code < 0)
		handle_error(data, msg);
}

void	handle_invalid_command(t_data *data)
{
	data->exec->return_code = EXIT_NOT_FOUND_COMMAND;
	handle_error(data, "command not found");
}

void	handle_syntax_error(t_data *data, char *token_str)
{
	printerr_syntax(token_str);
	free_data(data);
	exit(EXIT_SYNTAX_ERROR);
}

void	check_alloc(t_data *data, void *allocated)
{
	if (!allocated)
		handle_error(data, "memory error");
}

