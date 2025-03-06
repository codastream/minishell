#include "shell.h"

void	remove_quotes(t_data *data, char **arg, int start_quote_index, int end_quote_index)
{
	int	  i;
	int	  j;
	char  *trimmed;

	i = 0;
	j = 0;
	trimmed = ft_calloc(ft_strlen(*arg) - 1, sizeof(char));
	check_alloc(data, trimmed);
	while ((*arg)[i])
	{
		if (i != start_quote_index && i != end_quote_index)
		{
			trimmed[j] = (*arg)[i];
			j++;
		}
		i++;
	}
	free(*arg);
	*arg = trimmed;
}

int  handle_pair_of_quotes(t_data *data, char **arg, int i, char quote)
{
	int	  start_quote_index;

	start_quote_index = i;
	if ((*arg)[i])
	{
		i++;
		while ((*arg)[i] && (*arg)[i] != quote)
			i++;
		if ((*arg)[i])
		{
			remove_quotes(data, arg, start_quote_index, i);
			i = i - 2;
		}
	}
	return (i);
}

void	handle_quote_in_arg(t_data *data, char **arg)
{
	int	i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\"')
			i = handle_pair_of_quotes(data, arg, i, '"');
		if ((*arg)[i] == '\'')
			i = handle_pair_of_quotes(data, arg, i, '\'');
		i++;
	}
}

int	handle_quotes(t_data *data, t_token **tokens, t_token *token)
{
	int		i;
	char	**name_with_args;

	(void) tokens;
	if (token->type != T_COMMAND || !token->string)
		return (EXIT_IGNORE);
	update_command_from_string(data, token->command, token->string);
	name_with_args = token->command->command_args;
	i = 0;
	while (name_with_args[i])
	{
		handle_quote_in_arg(data, &name_with_args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
