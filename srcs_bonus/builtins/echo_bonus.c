/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:18 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:54:58 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	is_correct_option(char *option)
{
	int	i;

	i = 0;
	i++;
	while (option[i])
	{
		if (option[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	check_option(char **args, int *i, bool *should_print_newline)
{
	while (args[*i] && args[*i][0] == '-' && is_correct_option(args[*i]))
	{
		*should_print_newline = false;
		(*i)++;
	}
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
	check_option(command->command_args, &i, &should_print_newline);
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
