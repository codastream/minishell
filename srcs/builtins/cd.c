#include "shell.h"

void	ft_cd(t_data *data, t_token *token)
{
	char		*path;
	t_command	*command;

	command = token->command;
	if (command->command_args[2])
	{
		ft_printfd(2, "cd: too many arguments\n");
		ft_hash_update(data->vars, LAST_RETURN_CODE, "1");
		return ;
	}
	if (!(command->command_args)[1])
	{
		chdir(ft_hash_get(data->vars, "HOME"));
		return ;
	}
	path = ft_strjoinfree(getpwd(data), "/", 1);
	check_alloc(data, path);
	path = ft_strjoinfree(path, (command->command_args)[1], 1);
	check_alloc(data, path);
	if (chdir(path) < 0)
		handle_strerror(data, command->command_args[1], EXIT_FAILURE, false);
	free(path);
}
