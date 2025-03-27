/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:05 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:08:43 by fpetit           ###   ########.fr       */
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
