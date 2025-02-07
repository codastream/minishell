#include "shell.h"

void	ft_first_exit(t_data *data, t_command *command)
{
	ft_free_2d_char_null_ended(command->command_args);
//	free_data(data);
	(void)data;
	exit(0); // recuperer une variable d'environement si autoriser
}

void	ft_first_echo(t_command *command)
{
	int	i;

	i = 1;
	if (!(command->command_args)[0])
		return ;
	if (!ft_strcmp((command->command_args)[i], "-n"))
		i++;
	while ((command->command_args)[i])
		printf("%s", (command->command_args)[i++]);
	if (ft_strcmp((command->command_args)[1], "-n"))
		printf("\n");
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

void	ft_first_pwd(void)
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
}

void	ft_first_cd(t_command *command)
{
	char	*path;

	path = ft_joinfree(getpwd(), "/");
	path = ft_joinfree(path, (command->command_args)[1]);
	if (chdir(path) < 0)
		printf("error\n");
	free(path);
}

void	try_exec_first_buildins(t_data *data, t_command *command)
{
	if (!ft_strcmp((command->command_args)[0], "exit"))
		ft_first_exit(data, command);
	if (!ft_strcmp((command->command_args)[0], "echo"))
		ft_first_echo(command);
	if (!ft_strcmp((command->command_args)[0], "cd"))
		ft_first_cd(command);
	if (!ft_strcmp((command->command_args)[0], "pwd"))
		ft_first_pwd();
}
