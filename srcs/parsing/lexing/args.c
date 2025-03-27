#include "shell.h"

int	remove_empty_args(t_data *data, t_token **tokens, t_token *token)
{
	int		i;
	int		argc;
	char	*arg;
	char	**new_args;
	int		e;
	bool	has_command;

	(void) tokens;
	if (token->type != T_COMMAND || !token->command->command_args)
		return (EXIT_IGNORE);
	i = 0;
	argc = 0;
	has_command = false;
	while (token->command->command_args[i])
	{
		arg = token->command->command_args[i];
		if (!has_command && arg)
		{
			has_command = true;
			argc++;
		}
		else if (has_command && arg)
			argc++;
		i++;
	}
	if (argc == 0)
		return (EXIT_IGNORE);
	new_args = ft_calloc(argc + 1, sizeof(char *));
	check_alloc(data, new_args);
	i = 0;
	e = 0;
	has_command = false;
	while (token->command->command_args[i])
	{
		arg = token->command->command_args[i];
		if (!has_command && arg)
		{
			has_command = true;
			new_args[e++] = arg;
		}
		else if (has_command && arg)
			new_args[e++] = arg;
		else
			free(arg);
		i++;
	}
	free(token->command->command_args);
	token->command->command_args = new_args;
	if (ft_strcmp(token->command->command_args[0], \
		token->command->command_name))
	{
		free(token->command->command_name);
		{
			token->command->command_name = ft_strdup(token->command->command_args[0]);
			check_alloc(data, token->command->command_name);
		}
	}
	return (EXIT_SUCCESS);
}
