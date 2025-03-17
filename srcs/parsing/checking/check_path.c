#include "shell.h"

bool	is_absolute_path(char *s)
{
	if (ft_strncmp(s, "/", 1) == 0)
		return (true);
	return (false);
}

bool	is_path(char *s)
{
	if (ft_strncmp(s, "/", 1) == 0 \
		|| ft_strncmp(s, "./", 2) == 0 \
		|| ft_strncmp(s, "../", 3) == 0 \
	)
		return (true);
	return (false);
}

static char	*find_in_paths(t_data *data, char **splitted_paths, char *name)
{
	int		i;
	char	*pathname;
	char	*path_elems[2];

	i = 0;
	while (splitted_paths[i])
	{
		path_elems[0] = splitted_paths[i];
		path_elems[1] = name;
		pathname = ft_multistrjoin(2, path_elems, "/");
		check_alloc(data, pathname);
		if (access(pathname, X_OK) == 0)
			break ;
		free(pathname);
		pathname = NULL;
		i++;
	}
	return (pathname);
}

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
	struct		stat stats;
	int			statcode;

	statcode = stat(arg, &stats);
	if (statcode == 0 && S_ISDIR(stats.st_mode))
	{
		handle_custom_error_source_exit(data, arg, NULL, EXIT_PERMISSION_DENIED);
		return (NULL);
	}
	code = access(arg, F_OK);
	if (code != 0)
		return (NULL);
	code = access(arg, X_OK);
	if (code != 0 || !arg[1] || !ft_isalnum(arg[1]))
	{
		handle_custom_error_source_exit(data, arg, NULL, EXIT_PERMISSION_DENIED);
		return (NULL);
	}
	else
		return (ft_strdup(arg));
}

static char	*get_pathname_for_relative_patharg(t_data *data, char *arg)
{
	struct		stat stats;
	int			statcode;
	int			code;

	statcode = stat(arg, &stats);
	if (statcode == 0 && S_ISDIR(stats.st_mode))
	{
		handle_custom_error_source_exit(data, arg, MSG_IS_DIRECTORY, EXIT_PERMISSION_DENIED);
		return (NULL);
	}
  check_existing_file(data, arg);
	code = access(arg, X_OK);
	if (code == 0)
	{
		return (ft_strdup(arg));
	}
	else if (!ft_strncmp(arg, "../", 3))
	{
		handle_custom_error_source_exit(data, arg, NULL, EXIT_PERMISSION_DENIED);
		return (NULL);
	}
	else if (code != 0 && statcode == 0)
		handle_custom_error_source_exit(data, arg, NULL, EXIT_PERMISSION_DENIED);
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
	paths = ft_hash_get(data->vars, "PATH");
	if (!paths)
		return (NULL);
	splitted_paths = ft_split(paths, ':');
	check_alloc(data, splitted_paths);
	pathname = find_in_paths(data, splitted_paths, command->command_name);
	ft_free_2d_char_null_ended(splitted_paths);
	return (pathname);
}
