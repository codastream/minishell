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

char	*get_checked_pathmame(t_data *data, t_command *command)
{
	char		*path;
	char		**splitted_paths;
	char		*pathname;
	struct		stat stats;
	int			code;

	code = stat(command->command_args[0], &stats);
	if (code == 0 && S_ISDIR(stats.st_mode))
		return (NULL);
	code = access(command->command_name, X_OK);
	if (code == 0)
		return (ft_strdup(command->command_name));
	else if (code != 0 && !ft_strncmp(command->command_name, "./", 2))
		return (NULL);
	else if (code != 0 && is_path(command->command_name))
		handle_custom_error_source_exit(data, command->command_name, NULL, EXIT_PERMISSION_DENIED);
	path = ft_hash_get(data->vars, "PATH");
	if (!path)
		return (NULL);
	splitted_paths = ft_split(path, ':');
	check_alloc(data, splitted_paths);
	pathname = find_in_paths(data, splitted_paths, command->command_name);
	ft_free_2d_char_null_ended(splitted_paths);
	return (pathname);
}
