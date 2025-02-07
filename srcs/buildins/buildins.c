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

void	ft_exit(t_data *data, t_command *command)
{
	ft_free_2d_char_null_ended(command->command_args);
//	free_data(data);
	(void)data;
	exit(0); // recuperer une variable d'environement si autoriser
}

void	ft_echo(t_data *data, t_command *command)
{
	int	i;

	i = 1;
	if (!(command->command_args)[0])
		ft_exit(data, command);
	if (!ft_strcmp((command->command_args)[i], "-n"))
		i++;
	while ((command->command_args)[i])
		printf("%s", (command->command_args)[i++]);
	if (ft_strcmp((command->command_args)[1], "-n"))
		printf("\n");
	ft_exit(data, command);
}
/*
void	ft_env(t_data *data, t_command *command)
{
	int	i;

	i = 0;
	if (!data->hash)
		ft_exit(data, command);
	while (envp[i])
		printf("%s\n", envp[i++]);
	ft_exit(command, envp);
}*/

void	ft_pwd(t_data *data, t_command *command)
{
	int		size;
	char	*buffer;

	size = 2048;
	buffer = malloc(size);
	while (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		size = size * 2;
		buffer = malloc(size);
	}
	printf("%s\n", buffer);
	free(buffer);
	ft_exit(data, command);
}

char	*getpwd(void)
{
	int		size;
	char	*buffer;

	size = 2048;
	buffer = malloc(size);
	while (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		size = size * 2;
		buffer = malloc(size);
	}
	return(buffer);
}

void	ft_cd(t_data *data, t_command *command)
{
	char	*path;

	path = ft_joinfree(getpwd(), "/");
	path = ft_joinfree(path, (command->command_args)[1]);
	if (chdir(path) < 0)
		ft_exit(data, command);
	free(path);
	ft_pwd(data, command);
	ft_exit(data, command);
}

void	try_exec_buildins(t_data *data, t_command *command)
{
	if (!ft_strcmp((command->command_args)[0], "exit"))
		ft_exit(data, command);
	if (!ft_strcmp((command->command_args)[0], "echo"))
		ft_echo(data, command);
	if (!ft_strcmp((command->command_args)[0], "cd"))
		ft_cd(data, command);
	if (!ft_strcmp((command->command_args)[0], "pwd"))
		ft_pwd(data, command);
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
	return (false);
}
