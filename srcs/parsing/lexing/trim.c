#include "shell.h"

static void	remove_quotes(t_data *data, char **arg, \
		int start_quote_index, int end_quote_index)
{
	int		i;
	int		j;
	char	*trimmed;

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

static int	handle_pair_of_quotes(t_data *data, char **arg, int i, char quote)
{
	int	start_quote_index;

	start_quote_index = i;
	if ((*arg)[i])
	{
		i++;
		while ((*arg)[i] && (*arg)[i] != quote)
			i++;
		if ((*arg)[i])
		{
			remove_quotes(data, arg, start_quote_index, i);
			i = i - 1;
		}
	}
	return (i);
}

int	remove_extreme_double_quotes(t_data *data, char **s)
{
	int	first_quote_index;
	int	last_quote_index;

	first_quote_index = ft_strchri(*s, '"');
	last_quote_index = ft_strrchri(*s, '"');
	while (first_quote_index != -1 && last_quote_index != -1 && first_quote_index != last_quote_index)
	{
		remove_quotes(data, s, first_quote_index, last_quote_index);
		first_quote_index = ft_strchri(*s, '"');
		last_quote_index = ft_strrchri(*s, '"');
	}
	return (-1);
}

void	handle_quote_in_arg(t_data *data, char **arg)
{
	int	i;

	i = 0;
	while ((*arg)[i])
	{
		if (arg[0][i] == '"' && check_closing_doublequotes(data, *arg))
		{
			i = remove_extreme_double_quotes(data, arg);
		}
		else if ((*arg)[i] == '"' && !check_closing_doublequotes(data, *arg))
			i = handle_pair_of_quotes(data, arg, i, '"');
		if (i < 0)
			break ;
		if ((*arg)[i] == '\'')
			i = handle_pair_of_quotes(data, arg, i, '\'');
		if (i < 0)
			break ;
		if ((*arg)[i] && (*arg)[i] != '\'' && (*arg)[i] != '"')
			i++;
	}
}

void	handle_quote_in_command_arg(t_data *data, char **arg)
{
	char	*new_arg;

	if (is_surrounded_by_pairofchar(*arg, '\''))
	{
		new_arg = ft_strtrim(*arg, "'");
		check_alloc(data, new_arg);
		free(*arg);
		*arg = new_arg;
	}
	handle_quote_in_arg(data, arg);
}

int	handle_quotes(t_data *data, t_token **tokens, t_token *token)
{
	int		i;
	char	**name_with_args;

	(void) tokens;
	if (token->type != T_COMMAND || !token->command->command_args)
		return (EXIT_IGNORE);
	// update_command_from_string(data, token->command, token->string);
	name_with_args = token->command->command_args;
	if (!name_with_args[0])
		return (EXIT_IGNORE);
	i = 0;
	while (name_with_args[i])
	{
		handle_quote_in_command_arg(data, &name_with_args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
