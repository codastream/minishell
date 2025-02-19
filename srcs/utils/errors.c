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
	ft_printfd(2, "%sSyntax error near unexpected token '%s'%s\n", P_RED, tokenstr, P_NOC);
}

// should also handle free_after_exec ? + exit with custom code
// void	handle_skippable_error(t_data *data, char *msg, int code)
// {

// }

void	handle_fatal_error(t_data *data, char *msg, int code)
{
	printerr(msg);
	free_after_exec(data);
	free_data(data);
	exit(code);
}

void	handle_code(t_data *data, int code, char *msg)
{
	if (code < 0)
		handle_fatal_error(data, msg, code);
}

// void	handle_invalid_command(t_data *data)
// {
// 	printerr("command not found");
// 	free_after_exec(data);
// 	free_data(data);
// 	exit(EXIT_NOT_FOUND_COMMAND);
// }

void	handle_quote_error(t_data *data)
{
	printerr(MSG_SYNTAX_QUOTE_ERROR);
	ft_hash_remove(data->vars, LAST_RETURN_CODE);
	reset(data->line);
	reset(data->prompt);
}

void	handle_syntax_error(t_data *data, char *token_str)
{
	char	*last_code;

	printerr_syntax(token_str);
	last_code = ft_itoa(EXIT_SYNTAX_ERROR);
	ft_hash_update(data->vars, LAST_RETURN_CODE, last_code);
	free(last_code);
	free_after_parsing(data);
}

void	check_alloc(t_data *data, void *allocated)
{
	if (!allocated)
		handle_fatal_error(data, MSG_MEMORY_ERROR, EXIT_FAILURE);
}

