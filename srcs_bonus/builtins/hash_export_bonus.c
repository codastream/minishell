/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_export_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:10 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:54:48 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	append_export(t_data *data, char **cmd)
{
	char	*result;

	result = ft_hash_get(data->localvars, cmd[0]);
	if (!result)
	{
		ft_hash_insert(data->localvars, cmd[0], cmd[2]);
	}
	else
	{
		result = ft_strjoin(result, cmd[2]);
		ft_hash_update(data->localvars, cmd[0], result);
		free(result);
	}
}

void	supress_export(t_data *data, char **cmd)
{
	ft_hash_remove(data->localvars, cmd[0]);
	ft_hash_insert(data->localvars, cmd[0], cmd[2]);
}
