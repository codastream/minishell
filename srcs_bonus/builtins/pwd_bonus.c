/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:30:34 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:54:47 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*getpwd(t_data *data)
{
	int		size;
	char	*buffer;

	(void)data;
	size = 4096;
	buffer = ft_calloc(1, size);
	check_alloc(data, buffer);
	getcwd(buffer, size);
	return (buffer);
}

bool	has_invalid_option(t_data *data, t_token *token)
{
	int		i;
	int		j;
	char	**command_args;

	command_args = token->command->command_args;
	if (command_args[1])
	{
		i = 1;
		while (command_args[i])
		{
			j = 0;
			if (command_args[i][j] != '-')
				return (false);
			while (command_args[i][j] == '-' && j < 2)
				j++;
			if (command_args[i][j])
			{
				update_last_return(data, EXIT_SYNTAX_ERROR);
				return (true);
			}
			i++;
		}
	}
	return (false);
}

void	ft_pwd(t_data *data, t_token *token)
{
	int		size;
	char	*buffer;

	if (has_invalid_option(data, token))
	{
		printerr_source("pwd", MSG_USAGE_NO_OPTS);
		return ;
	}
	size = 4096;
	buffer = malloc(size);
	check_alloc(data, buffer);
	if (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		return ;
	}
	ft_printfd(token->out, "%s\n", buffer);
	free(buffer);
	update_last_return(data, EXIT_SUCCESS);
}
