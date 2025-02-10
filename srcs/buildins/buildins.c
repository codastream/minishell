#include "shell.h"

char	*ft_joinfree(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (!str1 || !str2)
		return (NULL);
	result = ft_calloc(ft_strlen(str1) + ft_strlen(str2) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (str1[i])
	{
		result[i] = str1[i];
		i++;
	}
	while (str2[j])
		result[i++] = str2[j++];
	free(str1);
	return (result);
}

void	try_exec_buildins(t_data *data, t_command *command)
{
	if (!ft_strcmp((command->command_args)[0], "exit"))
		ft_exit(data, command);
	if (!ft_strcmp((command->command_args)[0], "echo"))
	{
		ft_echo(command);
		ft_exit(data, command);
	}
	if (!ft_strcmp((command->command_args)[0], "cd"))
	{
		ft_cd(data, command);
		ft_exit(data, command);
	}
	if (!ft_strcmp((command->command_args)[0], "pwd"))
	{
		ft_pwd();
		ft_exit(data, command);
	}
	if (!ft_strcmp((command->command_args)[0], "env"))
	{
		ft_env(data->vars);
		ft_exit(data, command);
	}
	if (!ft_strcmp((command->command_args)[0], "unset"))
	{
		ft_unset(data, command);
		ft_exit(data, command);
	}
}

bool	is_buildins(t_command *command)
{
	if (!ft_strcmp((command->command_args)[0], "exit"))
		return (true);
	if (!ft_strcmp((command->command_args)[0], "echo"))
		return (true);
	if (!ft_strcmp((command->command_args)[0], "cd"))
		return (true);
	if (!ft_strcmp((command->command_args)[0], "pwd"))
		return (true);
	if (!ft_strcmp((command->command_args)[0], "env"))
		return (true);
	if (!ft_strcmp((command->command_args)[0], "unset"))
		return (true);
	return (false);
}
