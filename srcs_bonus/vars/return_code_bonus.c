/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_code_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:37:16 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:52:59 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_last_return(t_data *data, int code)
{
	char	*code_s;

	code_s = ft_itoa(code);
	check_alloc(data, code_s);
	ft_hash_update(data->localvars, LAST_RETURN_CODE, code_s);
	free(code_s);
}

int	get_last_return(t_data *data)
{
	int		code;
	char	*code_str;

	code_str = ft_hash_get(data->localvars, LAST_RETURN_CODE);
	code = ft_atoi(code_str);
	return (code);
}
