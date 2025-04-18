/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:47:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/30 19:46:50 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * checks that pipe integrates into following patterns
 * <word> OR <redir file> | <word> OR <redir file>
 */
int	check_pipe(t_data *data, t_token **tokens, t_token *token)
{
	(void) tokens;
	if (token->type == T_OR)
	{
		handle_syntax_error(data, "|");
		return (EXIT_SYNTAX_ERROR);
	}
	if (token->type != T_PIPE)
		return (EXIT_IGNORE);
	if (!token->prev || !token->next)
	{
		handle_syntax_error(data, token->string);
		return (EXIT_SYNTAX_ERROR);
	}
	if (token->prev->type != T_WORD && !is_file(token->prev))
	{
		handle_syntax_error(data, token->string);
		return (EXIT_SYNTAX_ERROR);
	}
	if (token->next->type != T_WORD && !is_redir_operator(token->next))
	{
		handle_syntax_error(data, token->next->string);
		return (EXIT_SYNTAX_ERROR);
	}
	return (EXIT_SUCCESS);
}
