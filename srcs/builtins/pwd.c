#include "shell.h"

char	*getpwd(t_data *data)
{
	int		size;
	char	*buffer;

	size = 2048;
	buffer = malloc(size);
	check_alloc(data, buffer);
	while (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		size = size * 2;
		buffer = malloc(size);
	}
	return (buffer);
}

bool	has_invalid_option(t_data *data, t_token *token)
{
	int		i;
	int		j;
	char	**command_args;

	command_args = token->command->command_args;
	if (command_args[1])
	{
		i = 1;
		while (command_args[i])
		{
			j = 0;
			if (command_args[i][j] != '-')
				return (false);
			while (command_args[i][j] == '-' && j < 2)
				j++;
			if (command_args[i][j])
			{
				update_last_return(data, EXIT_SYNTAX_ERROR);
				return (true);
			}
			i++;
		}
	}
	return (false);
}

void	ft_pwd(t_data *data, t_token *token)
{
	int		size;
	char	*buffer;

	if (has_invalid_option(data, token))
		return ;
	size = 2048;
	buffer = malloc(size);
	check_alloc(data, buffer);
	while (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		size = size * 2;
		buffer = malloc(size);
		check_alloc(data, buffer);
	}
	ft_printfd(token->out, "%s\n", buffer);
	free(buffer);
	update_last_return(data, EXIT_SUCCESS);
}
