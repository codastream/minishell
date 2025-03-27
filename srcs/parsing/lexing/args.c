/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:59:21 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 19:02:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	count_valid_args(t_token *token)
{
	int		i;
	int		argc;
	char	*arg;
	bool	has_command;

	argc = 0;
	i = 0;
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
	return (argc);
}

static void	update_args(t_data *data, t_token *token, int argc)
{
	char	**new_args;
	char	*arg;
	bool	has_command;
	int		i;
	int		e;

	new_args = ft_calloc(argc + 1, sizeof(char *));
	check_alloc(data, new_args);
	i = 0;
	e = 0;
	has_command = false;
	while (token->command->command_args[i])
	{
		arg = token->command->command_args[i];
		if (!has_command)
			has_command = true;
		if (arg)
			new_args[e++] = arg;
		else
			free(arg);
		i++;
	}
	free(token->command->command_args);
	token->command->command_args = new_args;
}

int	remove_empty_args(t_data *data, t_token **tokens, t_token *token)
{
	int		argc;

	(void) tokens;
	if (token->type != T_COMMAND || !token->command->command_args)
		return (EXIT_IGNORE);
	argc = count_valid_args(token);
	if (argc == 0)
		return (EXIT_IGNORE);
	update_args(data, token, argc);
	if (ft_strcmp(token->command->command_args[0], \
		token->command->command_name))
	{
		free(token->command->command_name);
		{
			token->command->command_name = \
				ft_strdup(token->command->command_args[0]);
			check_alloc(data, token->command->command_name);
		}
	}
	return (EXIT_SUCCESS);
}
