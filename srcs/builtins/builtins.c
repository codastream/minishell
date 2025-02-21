#include "shell.h"

char	*ft_joinfree(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (!str1 && str2)
		return (ft_strdup(str2));
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

void	try_exec_builtin(t_data *data, t_token *token, t_command *command)
{
	try_exec_single_builtin(data, token, command);
	if (is_builtin(data, command))
	{
		pop_all_fd(&data->fds);
		ft_exit(data, token);
	}
}

bool	is_builtin(t_data *data, t_command *command)
{
	int	i;

	i = 0;
	while (data->exec->builtins[i])
	{
		if (!ft_strcmp((command->command_args)[0], data->exec->builtins[i]))
			return (true);
		i++;
	}
	return (false);
}
