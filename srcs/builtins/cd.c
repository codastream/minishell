/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:22 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/08 23:05:23 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * returns false if cd should return
 */
static bool	are_valid_cd_args(t_data *data, char **command_args)
{
	int	arg_count;

	arg_count = ft_count_2dchar_null_ended(command_args);
	if (arg_count == 0)
		return (true);
	if (arg_count > 2)
	{
		handle_custom_error_source_builtin(data, "cd", MSG_TOO_MANY_ARGUMENTS, \
			EXIT_FAILURE);
		return (false);
	}
	if (!ft_strncmp(command_args[1], "---", 3))
	{
		update_last_return(data, EXIT_SYNTAX_ERROR);
		return (false);
	}
	return (true);
}

static char	*build_path_from_directory(t_data *data, char *path_arg)
{
	char	*path;
	char	*pwd;

	pwd = getpwd(data);
	path = ft_strjoinfree(pwd, "/", 1);
	check_alloc(data, path);
	path = ft_strjoinfree(path, path_arg, 1);
	check_alloc(data, path);
	return (path);
}

static char	*get_path_for_tilde(t_data *data, char **path_args, char *home_path)
{
	char	*path;

	if (!home_path)
		path = ft_hash_get(data->localvars, "PWD");
	else
		path = ft_subst(path_args[1], "~", home_path);
	return (path);
}

static char	*build_path(t_data *data, char **path_args, char *oldpwd)
{
	char	*path;
	char	*home_path;

	home_path = ft_hash_get(data->localvars, "HOME");
	if (!path_args[1] || !ft_strcmp(path_args[1], "--"))
	{
		if (!home_path)
		{
			printerr_source("cd", "HOME not set");
			return (NULL);
		}
		path = ft_strdup(home_path);
		check_alloc(data, path);
	}
	else if (!ft_strcmp(path_args[1], "-"))
		path = ft_strdup(oldpwd);
	else if (is_path(path_args[1]))
		path = ft_strdup(path_args[1]);
	else if (path_args[1][0] == '~')
		path = get_path_for_tilde(data, path_args, home_path);
	else
		path = build_path_from_directory(data, path_args[1]);
	return (path);
}

void	ft_cd(t_data *data, t_token *token)
{
	char		*path;
	t_command	*command;
	char		*oldpwd;

	command = token->command;
	if (!are_valid_cd_args(data, command->command_args))
		return ;
	oldpwd = update_oldpwd(data);
	path = build_path(data, command->command_args, oldpwd);
	free(oldpwd);
	if (!path)
		path = ft_strdup(ft_hash_get(data->localvars, "PWD"));
	if (!path || chdir(path) < 0)
	{
		free(path);
		handle_strerror(data, command->command_args[1], EXIT_FAILURE, false);
		return ;
	}
	free(path);
	path = getpwd(data);
	print_path_if_needed(command, token, path);
	ft_hash_update(data->localvars, "PWD", path);
	free(path);
	update_last_return(data, EXIT_SUCCESS);
}
