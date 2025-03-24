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
		update_last_error(data, EXIT_SYNTAX_ERROR);
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

	if (!path_args[1] || !ft_strcmp(path_args[1], "--"))
		path = ft_strdup(ft_hash_get(data->vars, "HOME"));
	else if (!ft_strcmp(path_args[1], "-"))
		path = ft_strdup(ft_hash_get(data->vars, "OLDPWD"));
	else if (is_path(path_args[1]))
		path = ft_strdup(path_args[1]);
	else if (path_args[1][0] == '~')
		path = ft_subst(path_args[1], "~", ft_hash_get(data->vars, "HOME"));
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
	if (ft_strcmp(ft_hash_get(data->vars, "PWD"), oldpwd))
		ft_hash_update(data->vars, "OLDPWD", oldpwd);
	free(oldpwd);
	path = build_path(data, command->command_args);
	if (!path || !path[0])
	{
		free(path);
		return ;
	}
	if (chdir(path) < 0)
		handle_strerror(data, command->command_args[1], EXIT_FAILURE, false);
	free(path);
	path = getpwd(data);
	if (command->command_args && command->command_args[1] && !ft_strcmp("-", command->command_args[1]))
		ft_printfd(token->out, path);
	ft_hash_update(data->vars, "PWD", path);
	free(path);
}
