#include "shell.h"

/*
 * if the first argument starts with a dot
 * returns error if
 * no path after dot
 * the path does not refers to a directory
 * the
 */
int	check_executable(t_data *data, t_token *token)
{
	struct stat stats;
	char		*path;
	int			code;

	path = token->command->command_args[0];
	if (!ft_strcmp(path, "."))
		handle_custom_error_source_exit(data, path, MSG_FILENAME_ARGUMENT_REQUIRED, EXIT_SYNTAX_ERROR);
	if (is_path(path))
	{
		code = stat(path, &stats);
		if (code == 0 && S_ISDIR(stats.st_mode))
			handle_custom_error_source_exit(data, path, MSG_IS_DIRECTORY, EXIT_PERMISSION_DENIED);
// 		handle_and_exit_if_negative(data, code, strerror(errno));
		if (access(path, X_OK) != 0)
			handle_custom_error_source_exit(data, path, strerror(errno), EXIT_PERMISSION_DENIED);
	}
	token->command->pathname = get_checked_pathmame(data, token->command);
	if (!token->command->pathname)
		handle_custom_error_source_exit(data, token->command->command_name, MSG_CMD_NOT_FOUND, EXIT_CMD_NOT_FOUND);
	return (EXIT_SUCCESS);
}
