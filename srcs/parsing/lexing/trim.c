/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:58:52 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/28 16:53:57 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	remove_quotes(t_data *data, char **arg, \
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

int	handle_quotes(t_data *data, t_token **tokens, t_token *token)
{
	int		i;
	char	**name_with_args;

	(void) tokens;
	if (token->type != T_COMMAND || !token->command->command_args)
		return (EXIT_IGNORE);
	name_with_args = token->command->command_args;
	if (!name_with_args[0])
		return (EXIT_IGNORE);
	i = 0;
	while (name_with_args[i])
	{
		handle_quote_in_arg(data, &name_with_args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
