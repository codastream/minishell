/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:58:55 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/07 19:33:14 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_tokens_nb(t_token **tokens)
{
	int		size;
	t_token	*current;

	current = *tokens;
	if (!current)
		return (0);
	size = 1;
	while (current->next)
	{
		size++;
		current = current->next;
	}
	return (size);
}

t_token	*get_last(t_token **tokens)
{
	t_token	*current;

	if (!*tokens)
		return (NULL);
	current = *tokens;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

bool	is_file(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == T_INFILE \
		|| token->type == T_EOF \
		|| token->type == T_OUTFILE_APPEND \
		|| token->type == T_OUTFILE_TRUNCATE \
	);
}

bool	is_redir_operator(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == T_REDIR_HEREDOC \
		|| token->type == T_REDIR_IN \
		|| token->type == T_REDIR_APPEND \
		|| token->type == T_REDIR_TRUNCATE \
	);
}

void	delete_token(t_token **tokens, t_token *token)
{
	if (token->prev)
		token->prev->next = token->next;
	else
	{
		*tokens = token->next;
		(*tokens)->prev = NULL;
	}
	if (token->next && token->prev)
		token->next->prev = token->prev;
	free_token(token);
}
