#include "shell.h"

void	ft_unset(t_data *data, t_token *token)
{
	int			i;
	t_command	*command;

	command = token->command;
	i = 1;
	update_last_return(data, EXIT_SUCCESS);
	while (command->command_args[i])
	{
		if ((command->command_args)[i][0] == '-')
			ft_hash_update(data->vars, LAST_RETURN_CODE, "2");
		ft_hash_remove(data->vars, (command->command_args)[i++]);
	}
}
