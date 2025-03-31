/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:05 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/31 21:15:54 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	is_valid_identifier(char *arg)
{
	if (!arg)
		return (false);
	if (arg[0] == '=')
		return (false);
	return (true);
}

char	**generate_export_split(char **result, char *cmd, int i, int j)
{
	int	code;

	code = ft_strndup(&result[1], cmd, j, i);
	if (!code)
		ft_free_2d_char_null_ended(result);
	code = ft_strndup(&result[2], cmd, i, ft_strlen(cmd));
	if (!code)
		ft_free_2d_char_null_ended(result);
	return (result);
}
