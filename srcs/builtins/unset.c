/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 15:31:32 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_unset(t_data *data, t_token *token)
{
	int			i;
	t_command	*command;

	command = token->command;
	i = 1;
	update_last_return(data, EXIT_SUCCESS);
	while (command->command_args[i])
	{
		if ((command->command_args)[i][0] == '-')
			ft_hash_update(data->localvars, LAST_RETURN_CODE, "2");
		ft_hash_remove(data->localvars, (command->command_args)[i++]);
	}
}
