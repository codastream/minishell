#include "shell.h"

void	try_exec_builtin_in_fork(t_data *data, t_token *token, t_command *command)
{
	int	code;

	try_exec_builtin(data, token, command);
	if (is_builtin(data, command))
	{
		code = get_last_return(data);
		pop_all_fd(&data->fds);
		free_all_data(data);
		exit(code);
	}
}

void	try_exec_builtin(t_data *data, t_token *token, \
t_command *command)
{
	int	i;

	i = 0;
	while (data->exec->builtins[i])
	{
		if (!ft_strcmp(command->command_args[0], data->exec->builtins[i]))
		{
			data->exec->builtin_ptrs[i](data, token);
			return ;
		}
		i++;
	}
}

bool	is_builtin(t_data *data, t_command *command)
{
	int	i;

	i = 0;
	if (!command->command_name)
		return (false);
	while (data->exec->builtins[i])
	{
		if (!ft_strcmp((command->command_args)[0], data->exec->builtins[i]))
			return (true);
		i++;
	}
	return (false);
}
