/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:01:49 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/09 16:12:21 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_path_if_needed(t_command *command, t_token *token, \
		char *path)
{
	if (command->command_args && command->command_args[1] \
		&& !ft_strcmp("-", command->command_args[1]))
	{
		ft_printfd(token->out, path);
		ft_printfd(token->out, "\n");
	}
}

char	*update_oldpwd(t_data *data)
{
	char		*pwd;
	char		*old;

	old = ft_strdup(ft_hash_get(data->localvars, "OLDPWD"));
	check_alloc(data, old);
	pwd = getpwd(data);
	if (ft_strcmp(pwd, ""))
		ft_hash_update(data->localvars, "OLDPWD", pwd);
	free(pwd);
	return (old);
}

char	*get_old_path(t_data *data)
{
	char	*path;
	char	*oldpwd;

	oldpwd = ft_hash_get(data->localvars, "OLDPWD");
	if (!oldpwd)
		path = "";
	else
		path = ft_strdup(oldpwd);
	return (path);
}
