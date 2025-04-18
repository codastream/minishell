/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:09:30 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:12:17 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handle_custom_error_source_noexit(t_data *data, char *error_source, \
			char *msg, int code)
{
	if (code == EXIT_CMD_NOT_FOUND)
		printerr_command_notfound(error_source);
	else if (msg && error_source)
		printerr_source(error_source, msg);
	update_last_error(data, code);
	free_all_data(data);
}

void	handle_custom_error_source_builtin(t_data *data, char *error_source, \
			char *msg, int code)
{
	if (code == EXIT_CMD_NOT_FOUND)
		printerr_command_notfound(error_source);
	else if (msg && error_source)
		printerr_source(error_source, msg);
	update_last_error(data, code);
	free_after_exec(data);
}

void	handle_custom_error_source_exit(t_data *data, char *error_source, \
			char *msg, int code)
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
	if (data->localvars)
		update_last_error(data, code);
	if (should_exit)
	{
		if (data)
			free_all_data(data);
		exit(code);
	}
}

void	handle_strerror(t_data *data, char *error_source, int code, \
			bool should_exit)
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
