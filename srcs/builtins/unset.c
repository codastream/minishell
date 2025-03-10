#include "shell.h"

void	ft_unset(t_data *data, t_token *token)
{
	int			i;
	t_command	*command;

	command = token->command;
	i = 1;
	while (command->command_args[i])
		ft_hash_remove(data->vars, (command->command_args)[i++]);
}
