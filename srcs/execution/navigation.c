#include "shell.h"

int	try_navigation(t_data *data, t_token *token)
{
	struct stat stats;
	char		*path;
	int			code;

	path = token->command->command_args[0];
	if (!ft_strcmp(path, "."))
	{
		handle_custom_error_source_exit(data, path, MSG_FILENAME_ARGUMENT_REQUIRED, EXIT_SYNTAX_ERROR);
	}
	code = stat(path, &stats);
	if (code == 0 && S_ISDIR(stats.st_mode))
		handle_custom_error_source_exit(data, path, MSG_IS_DIRECTORY, EXIT_PERMISSION_DENIED);
	if (token->type != T_COMMAND || token->command->command_args[0][0] != '.')
		return (EXIT_IGNORE);
	code = stat(path, &stats);
	handle_and_exit_if_negative(data, code, strerror(errno));
	if (access(path, X_OK) != 0)
		handle_custom_error_source_exit(data, path, strerror(errno), EXIT_PERMISSION_DENIED);
	return (EXIT_SUCCESS);
}
