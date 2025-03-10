#include "shell.h"

void	handle_custom_error_source_exit(t_data *data, char *error_source, char *msg, int code)
{
	if (code == EXIT_CMD_NOT_FOUND)
		printerr_command_notfound(error_source);
	else if (msg && error_source)
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

void	handle_and_exit_if_negative(t_data *data, int code, char *msg)
{
	if (code < 0)
		handle_custom_error(data, msg, code, true);
}
