#include "shell.h"

/*
 * displays an error msg on stderr with red text
 */
void	printerr(char *msg)
{
	ft_printfd(2, "%s%s%s\n", P_RED, msg, P_NOC);
}

void	printerr_source(char *error_source, char *msg)
{
	ft_printfd(2, "%s%s: %s%s\n", P_RED, error_source, msg, P_NOC);
}

void	printerr_syntax(char *tokenstr)
{
	ft_printfd(2, "%ssyntax error near unexpected token `%s'%s\n", P_RED, tokenstr, P_NOC);
}
void	printerr_strno(void)
{
	ft_printfd(2, "%s%s%s\n", P_RED, strerror(errno), P_NOC);
}
void	printerr_strno_source(char *error_source)
{
	ft_printfd(2, "%s%s: %s%s\n", P_RED, error_source, strerror(errno), P_NOC);
}

// void	handle_fatal_error(t_data *data, char *msg, int code)
// {
// 	printerr(msg);
// 	free_all_data(data);
// 	exit(code);
// }

void	update_last_error(t_data *data, int code)
{
	char	*code_str;

	code_str = ft_itoa(code);
	check_alloc(data, code_str);
	ft_hash_update(data->vars, LAST_RETURN_CODE, code_str);
	free(code_str);
}

void	handle_custom_error(t_data *data, char *msg, int code, bool should_exit)
{

	if (msg)
		printerr(msg);
	update_last_error(data, code);
	if (should_exit)
	{
		free_all_data(data);
		exit(code);
	}
}

void	handle_strerror(t_data *data, char *error_source, int code, bool should_exit)
{
	char	*code_str;

	if (!error_source)
		printerr_strno();
	else
		printerr_strno_source(error_source);
	update_last_error(data, code);
	if (should_exit)
	{
		free_all_data(data);
		exit(code);
	}
}

void	handle_builtin_error(t_data *data, t_command *command, char *msg, int code)
{
	printerr_source(command->command_name, msg);
	update_last_error(data, code);
	free_all_data(data);
	exit(code);
}

// void	build_wrongvar_msg(t_data *data, char *wrong_var, char *msg)
// {
// 	char	*full_msg;
// 	char	**tabs;

// 	tabs = ft_calloc(4, sizeof(char *));
// 	check_alloc(data, tabs);
// 	tabs[0] = "";
// 	tabs[1] = wrong_var;
// 	tabs[2] = ": ";
// 	tabs[3] = msg;

// 	full_msg = ft_multistrjoin(4, tabs, "");
// 	check_alloc(data, full_msg);
// 	data->exec->error_msg = full_msg;
// }

void	handle_and_exit_if_negative(t_data *data, int code, char *msg)
{
	if (code < 0)
		handle_custom_error(data, msg, code, true);
}

void	check_alloc(t_data *data, void *allocated)
{
	if (!allocated)
		handle_custom_error(data, MSG_MEMORY_ERROR, EXIT_FAILURE, true);
}

void	handle_quote_error(t_data *data)
{
	char	*last_code;

	printerr(MSG_SYNTAX_QUOTE_ERROR);
	last_code = ft_itoa(EXIT_SYNTAX_ERROR);
	ft_hash_update(data->vars, LAST_RETURN_CODE, last_code);
	free(last_code);
	reset(data->line);
	reset(data->prompt);
	// data->return_code = EXIT_SYNTAX_ERROR;
}

void	handle_syntax_error(t_data *data, char *token_str)
{
	char	*last_code;

	printerr_syntax(token_str);
	update_last_error(data, EXIT_SYNTAX_ERROR);
	free_after_parsing(data);
	// data->return_code = EXIT_SYNTAX_ERROR;
}

void	handle_child_error(t_data *data, t_command *command)
{
	if (command->has_invalid_redir)
	{
		free_all_data(data);
		exit(EXIT_FAILURE);
	}
	else
	{
		printerr_source(command->command_name, MSG_CMD_NOT_FOUND);
		free_all_data(data);
		exit(EXIT_CMD_NOT_FOUND);
	}
}
