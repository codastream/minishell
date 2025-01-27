/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:16:47 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/27 17:46:21 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * checks for pattern word | word
 * and assumes word are commands
 */
void	check_pipe(t_token *token)
{
	if (token->type != T_PIPE)
		return ;
	if (!token->prev || !token->next)
		handle_syntax_error(token->string);
	if (token->prev->type != T_WORD)
		token->prev->type = T_COMMAND;
	else
		handle_syntax_error(token->next->string);
	if (token->next->type == T_WORD)
		token->next->type = T_COMMAND;
	else
		handle_syntax_error(token->next->string);
}
