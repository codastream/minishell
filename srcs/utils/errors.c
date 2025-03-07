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

void	update_last_error(t_data *data, int code)
{
	char	*code_str;

	code_str = ft_itoa(code);
	check_alloc(data, code_str);
	ft_hash_update(data->vars, LAST_RETURN_CODE, code_str);
	free(code_str);
}

void	handle_custom_error_exit(t_data *data, char *error_source, char *msg, int code)
{
	if (msg && error_source)
		printerr_source(error_source, msg);
	update_last_error(data, code);
	free_all_data(data);
	exit(code);
}
/*
 * should exit only for fatal errors (ex : failed malloc)
 * or within a forked process
 */
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

void	handle_custom_error_source(t_data *data, char *error_source, int code, bool should_exit)
{
	if (code == EXIT_CMD_NOT_FOUND)
		ft_printfd(2, "%s%s: %s\n%s", P_RED, error_source, MSG_CMD_NOT_FOUND, P_NOC);
	update_last_error(data, code);
	if (should_exit)
	{
		free_all_data(data);
		exit(code);
	}
}

void	handle_strerror(t_data *data, char *error_source, int code, bool should_exit)
{
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

char	*build_wrongvar_msg(t_data *data, char *command_name, char *wrong_var, char *msg)
{
	char	*full_msg;
	char	**tabs;

	tabs = ft_calloc(5, sizeof(char *));
	check_alloc(data, tabs);
	tabs[0] = command_name;
	tabs[1] = ": ";
	tabs[2] = wrong_var;
	tabs[3] = ": ";
	tabs[4] = msg;

	full_msg = ft_multistrjoin(5, tabs, "");
	check_alloc(data, full_msg);
	return (full_msg);
}

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

void	handle_end_of_loop(t_data *data)
{
	int	code;

	code = get_last_return(data);
	free(data->prompt);
	free_vars_and_data(data);
	exit(code);
}

void	handle_non_interactive_end(t_data *data, char *step)
{
	int	code;

	code = get_last_return(data);
	if (PRINT == 1)
		printf("handle noninter end code %d\n", code);
	if (!strcmp(step, "beforeexec"))
	{
		free_vars_and_data(data);
	}
	else if (!strcmp(step, "afterexec"))
	{
		free_all_data(data);
	}
	exit(code);
}

void	handle_quote_error(t_data *data)
{
	printerr(MSG_SYNTAX_QUOTE_ERROR);
	update_last_error(data, EXIT_SYNTAX_ERROR);
	free_before_parsing(data);
}

void	handle_syntax_error(t_data *data, char *token_str)
{
	printerr_syntax(token_str);
	update_last_error(data, EXIT_SYNTAX_ERROR);
	free_after_parsing(data);
}

// void	handle_child_error(t_data *data, t_command *command)
// {
// 	if (command->has_invalid_redir)
// 	{
// 		free_all_data(data);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		printerr_source(command->command_name, MSG_CMD_NOT_FOUND);
// 		free_all_data(data);
// 		exit(EXIT_CMD_NOT_FOUND);
// 	}
// }
