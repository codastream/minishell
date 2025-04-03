/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:07:05 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 18:10:41 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	do_for_tokens_delete(t_data *data, t_token **tokens, \
		t_token *(*f)(t_data *, t_token **, t_token *, t_token *))
{
	t_token	*current;
	t_token	*tmp;

	tmp = NULL;
	if (!tokens)
		return (EXIT_FAILURE);
	current = *tokens;
	while (current)
	{
		current = f(data, tokens, current, tmp);
	}
	if (PRINT == 1)
		print_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	do_for_tokens(t_data *data, t_token **tokens, \
		int (*f)(t_data *, t_token **, t_token *))
{
	t_token	*current;
	int		code;

	if (!tokens)
		return (EXIT_FAILURE);
	current = *tokens;
	while (current)
	{
		code = f(data, tokens, current);
		if (code != EXIT_SUCCESS)
			return (code);
		if (current)
			current = current->next;
		else
			current = *tokens;
	}
	if (PRINT == 1)
		print_tokens(tokens);
	return (EXIT_SUCCESS);
}
