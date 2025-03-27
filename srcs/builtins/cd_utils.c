/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:01:49 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 16:02:25 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_oldpwd(t_data *data)
{
	char		*oldpwd;

	oldpwd = getpwd(data);
	if (ft_strcmp(oldpwd, "") && \
		ft_strcmp(ft_hash_get(data->localvars, "PWD"), oldpwd))
		ft_hash_update(data->localvars, "OLDPWD", oldpwd);
	free(oldpwd);
}
