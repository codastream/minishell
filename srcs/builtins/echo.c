#include "shell.h"

void	ft_echo(t_data *data, t_token *token)
{
	int			i;
	t_command	*command;

	(void) data;
	i = 1;
	command = token->command;
	if (!(command->command_args)[0])
		return ;
	if (!ft_strcmp((command->command_args)[i], "-n"))
		i++;
	while ((command->command_args)[i])
	{
		ft_printfd(token->out, "%s", (command->command_args)[i]);
		if ((command->command_args)[i + 1])
			ft_printfd(token->out, " ");
		i++;
	}
	if (ft_strcmp((command->command_args)[1], "-n"))
		ft_printfd(token->out, "\n");
}
