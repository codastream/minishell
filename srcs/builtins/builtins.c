#include "shell.h"

void	try_exec_builtin(t_data *data, t_token *token, t_command *command)
{
	try_exec_single_builtin(data, token, command);
	if (is_builtin(data, command))
	{
		pop_all_fd(&data->fds);
		ft_exit(data, token);
	}
}

void	try_exec_single_builtin(t_data *data, t_token *token, \
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
