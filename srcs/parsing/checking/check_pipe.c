/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:16:47 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/23 17:42:47 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_pipe(t_token *token)
{
	if (token->prev)
	{
		if (token->prev->type != T_COMMAND && token->prev->type != T_VAR)
			handle_syntax_error(token->next->string);
	};
}
