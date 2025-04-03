/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print_custom.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:09:22 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:12:10 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	printerr_command_notfound(char *command_name)
{
	ft_printfd(2, "%sCommand '%s' not found%s\n", P_RED, command_name, P_NOC);
}

void	printerr_syntax(char *tokenstr)
{
	ft_printfd(2, "%ssyntax error near unexpected token `%s'%s\n", P_RED, \
		tokenstr, P_NOC);
}
