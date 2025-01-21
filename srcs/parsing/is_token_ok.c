/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmassavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:16:47 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/19 19:16:59 by jmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.c"

bool	check_pipe(t_token *token)
{
	if (token->prev)
	{
		if ((token->prev)->type != t_COMMAND && (token->prev)->type != T_VAR)
			return (false);
	}
	else
		return(false);
	if (token->next)
	{
		if ((token->next)->type != t_COMMAND || (token->next)->type != T_VAR)
			return (false);
	}
	else
		return(false);
	return (true);
}

bool	is_token_ok(t_token *token)
{
	while (token)
	{
		if (token->type == T_PIPE)
		{
			if (check_pipe(t_token *token) == false)
				return (false);
		}
		token = token->next;
	}
	return (true);
}
