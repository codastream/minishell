/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:09:27 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:11:47 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*build_wrongvar_msg(t_data *data, char *command_name, char *wrong_var, \
			char *msg)
{
	char	*full_msg;
	char	**tabs;

	tabs = ft_calloc(6, sizeof(char *));
	check_alloc(data, tabs);
	tabs[0] = command_name;
	tabs[1] = ": ";
	tabs[2] = wrong_var;
	tabs[3] = ": ";
	tabs[4] = msg;
	full_msg = ft_multistrjoin(5, tabs, "");
	check_alloc(data, full_msg);
	free(tabs);
	return (full_msg);
}

void	update_last_error(t_data *data, int code)
{
	char	*code_str;

	code_str = ft_itoa(code);
	ft_hash_update(data->localvars, LAST_RETURN_CODE, code_str);
	free(code_str);
}

void	handle_and_exit_if_negative(t_data *data, int code, char *msg)
{
	if (code < 0)
		handle_custom_error(data, msg, code, true);
}
