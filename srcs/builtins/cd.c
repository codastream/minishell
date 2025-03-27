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
		handle_custom_error_source_builtin(data, "cd", MSG_TOO_MANY_ARGUMENTS, EXIT_FAILURE);
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

	path = ft_strjoinfree(getpwd(data), "/", 1);
	check_alloc(data, path);
	path = ft_strjoinfree(path, path_arg, 1);
	check_alloc(data, path);
	return (path);
}

static char	*build_path(t_data *data, char **path_args)
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
		path = home_path;
	}
	else if (!ft_strcmp(path_args[1], "-"))
		path = ft_strdup(ft_hash_get(data->localvars, "OLDPWD"));
	else if (is_path(path_args[1]))
		path = ft_strdup(path_args[1]);
	else if (path_args[1][0] == '~')
	{
		path = ft_subst(path_args[1], "~", home_path);
		if (!home_path)
			path = ft_hash_get(data->localvars, "PWD");
	}
	else
		path = build_path_from_directory(data, path_args[1]);
	return (path);
}

void	ft_cd(t_data *data, t_token *token)
{
	char		*path;
	char		*oldpwd;
	t_command	*command;

	command = token->command;
	if (!are_valid_cd_args(data, command->command_args))
		return ;
	oldpwd = getpwd(data);
	if (ft_strcmp(oldpwd, "") && ft_strcmp(ft_hash_get(data->localvars, "PWD"), oldpwd))
		ft_hash_update(data->localvars, "OLDPWD", oldpwd);
	free(oldpwd);
	path = build_path(data, command->command_args);
	if (!path)
		path = ft_strdup(ft_hash_get(data->localvars, "PWD"));
	if (chdir(path) < 0)
	{
		handle_strerror(data, command->command_args[1], EXIT_FAILURE, false);
		return ;
	}
	free(path);
	path = getpwd(data);
	if (command->command_args && command->command_args[1] && !ft_strcmp("-", command->command_args[1]))
		ft_printfd(token->out, path);
	ft_hash_update(data->localvars, "PWD", path);
	free(path);
	update_last_return(data, EXIT_SUCCESS);
}
