#include "shell.h"

int	remove_empty_args(t_data *data, t_token **tokens, t_token *token)
{
	int		i;
	int		argc;
	char	*arg;
	char	**new_args;
	int		e;

	(void) tokens;
	if (token->type != T_COMMAND || !token->command->command_args)
		return (EXIT_IGNORE);
	i = 0;
	argc = 0;
	argc++;
	while (token->command->command_args[i])
	{
		arg = token->command->command_args[i];
		if (i == 0 || (i > 0 && ft_strcmp(arg, "")))
			argc++;
		i++;
	}
	new_args = ft_calloc(argc + 1, sizeof(char *));
	check_alloc(data, new_args);
	i = 0;
	e = 0;
	while (token->command->command_args[i])
	{
		arg = token->command->command_args[i];
		if (i == 0 || (i > 0 && ft_strcmp(arg, "")))
			new_args[e++] = arg;
		else
			free(arg);
		i++;
	}
	free(token->command->command_args);
	token->command->command_args = new_args;
	return (EXIT_SUCCESS);
}
