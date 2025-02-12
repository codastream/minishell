#include "shell.h"

void	ft_exit(t_data *data, t_command *command)
{
	int	return_code;

	return_code = data->exec->return_code;
	(void)command;
	free_after_exec(data);
	ft_free_hashtable(data->vars);
	free_data(data);
	exit(return_code); // recuperer une variable d'environement si autoriser
}

void	ft_echo(t_token *token, t_command *command)
{
	int	i;

	i = 1;
	if (!(command->command_args)[0])
		return ;
	if (!ft_strcmp((command->command_args)[i], "-n"))
		i++;
	while ((command->command_args)[i])
		ft_printfd(token->out, "%s", (command->command_args)[i++]);
	if (ft_strcmp((command->command_args)[1], "-n"))
		ft_printfd(token->out, "\n");
	//	printf("\n");
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

// TODO use hashmap or tab with function pointers ?
void	try_exec_single_builtin(t_data *data, t_token *token, t_command *command)
{
	if (!ft_strcmp((command->command_args)[0], "exit"))
		ft_exit(data, command);
	else if (!ft_strcmp((command->command_args)[0], "echo"))
		ft_echo(token, command);
	else if (!ft_strcmp((command->command_args)[0], "cd"))
		ft_cd(data, command);
	else if (!ft_strcmp((command->command_args)[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp((command->command_args)[0], "env"))
		ft_env(data->vars);
	else if (!ft_strcmp((command->command_args)[0], "unset"))
		ft_unset(data, command);
}
