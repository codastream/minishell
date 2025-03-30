/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:01:49 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/30 19:06:27 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_path_if_needed(t_command *command, t_token *token, \
		char *path)
{
	if (command->command_args && command->command_args[1] \
		&& !ft_strcmp("-", command->command_args[1]))
	ft_printfd(token->out, path);
	ft_printfd(token->out, "\n");
}

void	update_oldpwd(t_data *data)
{
	char		*oldpwd;

	oldpwd = getpwd(data);
	if (ft_strcmp(oldpwd, "") && \
		ft_strcmp(ft_hash_get(data->localvars, "PWD"), oldpwd))
		ft_hash_update(data->localvars, "OLDPWD", oldpwd);
	free(oldpwd);
}
