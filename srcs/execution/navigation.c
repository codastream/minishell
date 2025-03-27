/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:34:51 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:35:58 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_navigation(t_data *data, char *path)
{
	struct stat	stats;
	int			code;

	code = stat(path, &stats);
	if (code == 0 && S_ISDIR(stats.st_mode))
		handle_custom_error_source_exit(data, path, MSG_IS_DIRECTORY, \
			EXIT_PERMISSION_DENIED);
}

/*
 * if the first argument starts with a dot
 * returns error if
 * no path after dot
 * the path does not refers to a directory
 */
int	check_executable(t_data *data, t_token *token)
{
	char		*path;

	path = token->command->command_args[0];
	if (!ft_strcmp(path, "."))
		handle_custom_error_source_exit(data, path, \
			MSG_FILENAME_ARGUMENT_REQUIRED, EXIT_SYNTAX_ERROR);
	if (!ft_strcmp(path, ".."))
		handle_custom_error_source_exit(data, token->command->command_name, \
			MSG_CMD_NOT_FOUND, EXIT_CMD_NOT_FOUND);
	token->command->pathname = get_checked_pathmame(data, token->command);
	if (!token->command->pathname)
		handle_custom_error_source_exit(data, token->command->command_name, \
			MSG_CMD_NOT_FOUND, EXIT_CMD_NOT_FOUND);
	return (EXIT_SUCCESS);
}
