/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:47:26 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:56:20 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_existing_file(t_data *data, char *args)
{
	int	code;

	code = access(args, R_OK);
	if (code != 0 && is_path(args))
		handle_custom_error_source_exit(data, args, NULL, 127);
}

static char	*get_pathname_for_absolute_patharg(t_data *data, char *arg)
{
	int			code;
	struct stat	stats;
	int			statcode;

	statcode = stat(arg, &stats);
	if (statcode == 0 && S_ISDIR(stats.st_mode))
	{
		handle_custom_error_source_exit(data, arg, NULL, \
			EXIT_PERMISSION_DENIED);
		return (NULL);
	}
	code = access(arg, F_OK);
	if (code != 0)
		return (NULL);
	code = access(arg, X_OK);
	if (code != 0 || !arg[1] || !ft_isalnum(arg[1]))
	{
		handle_custom_error_source_exit(data, arg, NULL, \
			EXIT_PERMISSION_DENIED);
		return (NULL);
	}
	else
		return (ft_strdup(arg));
}

static bool	check_is_directory(t_data *data, char *arg)
{
	struct stat	stats;
	int			statcode;

	statcode = stat(arg, &stats);
	if (statcode == 0 && S_ISDIR(stats.st_mode))
	{
		handle_custom_error_source_exit(data, arg, MSG_IS_DIRECTORY, \
			EXIT_PERMISSION_DENIED);
		return (true);
	}
	return (false);
}

static char	*get_pathname_for_relative_patharg(t_data *data, char *arg)
{
	int			code;

	if (check_is_directory(data, arg))
		return (NULL);
	code = access(arg, F_OK);
	if (!ft_strncmp(arg, "./", 2) && code != 0)
		return (NULL);
	code = access(arg, X_OK);
	if (code == 0)
	{
		if (is_elf_executable(data, arg) || is_script(data, arg))
			return (ft_strdup(arg));
		return (NULL);
	}
	else if (code != 0 && !ft_strncmp(arg, "./", 2))
		handle_custom_error_source_exit(data, arg, NULL, \
			EXIT_PERMISSION_DENIED);
	else if (code != 0 && is_path(arg))
		handle_custom_error_source_exit(data, arg, NULL, \
			EXIT_PERMISSION_DENIED);
	return (NULL);
}

char	*get_checked_pathmame(t_data *data, t_command *command)
{
	char		*arg;
	char		*paths;
	char		**splitted_paths;
	char		*pathname;

	arg = command->command_args[0];
	if (is_absolute_path(arg))
		return (get_pathname_for_absolute_patharg(data, arg));
	else if (ft_strstr(arg, "./"))
		return (get_pathname_for_relative_patharg(data, arg));
	paths = ft_hash_get(data->localvars, "PATH");
	if (!paths)
		return (NULL);
	splitted_paths = ft_split(paths, ':');
	check_alloc(data, splitted_paths);
	pathname = find_in_paths(data, splitted_paths, command->command_name);
	ft_free_2d_char_null_ended(splitted_paths);
	return (pathname);
}
