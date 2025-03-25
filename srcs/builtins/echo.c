#include "shell.h"

static bool	is_correct_option(char *option)
{
	int	i;

	i = 0;
	// if (option[i] != '-')
	// 	return (false);
	i++;
	while(option[i])
	{
		if (option[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	ft_echo(t_data *data, t_token *token)
{
	int			i;
	t_command	*command;
	bool		should_print_newline;

	(void) data;
	command = token->command;
	should_print_newline = true;
	if (!(command->command_args)[0])
	return ;
	i = 1;
	while (command->command_args[i] && command->command_args[i][0] == '-' && is_correct_option(command->command_args[i]))
	{
		should_print_newline = false;
		i++;
	}
	while ((command->command_args)[i])
	{
		ft_printfd(token->out, "%s", (command->command_args)[i]);
		if ((command->command_args)[i + 1])
			ft_printfd(token->out, " ");
		i++;
	}
	if (should_print_newline)
		ft_printfd(token->out, "\n");
	update_last_return(data, EXIT_SUCCESS);
}
