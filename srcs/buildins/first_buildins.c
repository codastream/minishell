#include "shell.h"

void	ft_exit(t_data *data, t_command *command)
{
	(void)command;
	free_after_exec(data);
	free_data(data);
	exit(0); // recuperer une variable d'environement si autoriser
}

void	ft_echo(t_command *command)
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

void	ft_env(t_hash *hash)
{
	int			i;
	t_keyval	**keyvals;
	t_keyval	*current;

	keyvals = hash->keyvals;
	i = 0;
	while (i < hash->capacity)
	{
		if (keyvals[i])
		{
			current = keyvals[i];
			while (current)
			{
				ft_printf("%s=%s\n", current->key, \
					(char *) current->value);
				current = current->next;
			}
		}
		i++;
	}
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
	return (buffer);
}

void	ft_pwd(void)
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

void	ft_cd(t_data *data,t_command *command)
{
	char	*path;

	if (!(command->command_args)[1])
	{
		chdir(ft_hash_get(data->vars, "HOME"));
		return ;
	}
	path = ft_joinfree(getpwd(), "/");
	path = ft_joinfree(path, (command->command_args)[1]);
	if (chdir(path) < 0)
		printf("error\n");
	free(path);
}

void	ft_unset(t_data *data, t_command *command)
{
	if (!(command->command_args)[1])
			return ;
	ft_hash_remove(data->vars, (command->command_args)[1]);
}

void	try_exec_first_buildins(t_data *data, t_command *command)
{
	if (!ft_strcmp((command->command_args)[0], "exit"))
		ft_exit(data, command);
	if (!ft_strcmp((command->command_args)[0], "echo"))
		ft_echo(command);
	if (!ft_strcmp((command->command_args)[0], "cd"))
		ft_cd(data, command);
	if (!ft_strcmp((command->command_args)[0], "pwd"))
		ft_pwd();
	if (!ft_strcmp((command->command_args)[0], "env"))
		ft_env(data->vars);
	if (!ft_strcmp((command->command_args)[0], "unset"))
		ft_unset(data, command);
}
