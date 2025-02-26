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
	ft_printfd(2, "%ssyntax error near unexpected token `%s'%s\n", P_RED, tokenstr, P_NOC);
}

void	handle_fatal_error(t_data *data, char *msg, int code)
{
	printerr(msg);
	free_all_data(data);
	exit(code);
}

void	handle_builtin_error(t_data *data, t_command *command, char *msg, int code)
{
	ft_printfd(2, "%s%s: %s%s\n", P_RED, command->command_name, msg, P_NOC);
	free_all_data(data);
	exit(code);
}

void	build_wrongvar_msg(t_data *data, char *wrong_var, char *msg)
{
	char	*full_msg;
	char	**tabs;

	tabs = ft_calloc(4, sizeof(char *));
	check_alloc(data, tabs);
	tabs[0] = "";
	tabs[1] = wrong_var;
	tabs[2] = ": ";
	tabs[3] = msg;

	full_msg = ft_multistrjoin(4, tabs, "");
	check_alloc(data, full_msg);
	data->exec->error_msg = full_msg;
}

void  handle_child_error(t_data *data, t_command *command)
{
  if (command->has_invalid_redir)
  {
    free_all_data(data);
    exit(EXIT_FAILURE);
  }
  else
    handle_command_not_found(data, "%s%s: command not found%s\n", command->command_name, EXIT_NOT_FOUND_COMMAND);
}

void	handle_command_not_found(t_data *data, char *msg, char *cmd, int code)
{
	ft_printfd(2, msg, P_RED, cmd, P_NOC);
	free_all_data(data);
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
	data->return_code = EXIT_SYNTAX_ERROR;
}

void	handle_syntax_error(t_data *data, char *token_str)
{
	char	*last_code;

	printerr_syntax(token_str);
	last_code = ft_itoa(EXIT_SYNTAX_ERROR);
	ft_hash_update(data->vars, LAST_RETURN_CODE, last_code);
	free(last_code);
	free_after_parsing(data);
	data->return_code = EXIT_SYNTAX_ERROR;
}

void	check_alloc(t_data *data, void *allocated)
{
	if (!allocated)
		handle_fatal_error(data, MSG_MEMORY_ERROR, EXIT_FAILURE);
}

