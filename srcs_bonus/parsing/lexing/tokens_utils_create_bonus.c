/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_create_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:58:59 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:53:40 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*new_token(t_data *data, t_tokentype type, int index, char *string)
{
	t_token	*token;

	(void) data;
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->index = index;
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	token->command = NULL;
	token->in = STDIN_FILENO;
	token->out = STDOUT_FILENO;
	if (string)
	{
		token->string = ft_strtrim(string, " ");
		if (!string)
			return (NULL);
	}
	else
		token->string = NULL;
	return (token);
}

void	add_token_back(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (!*tokens)
		*tokens = new;
	else
	{
		last = get_last(tokens);
		last->next = new;
		new->prev = last;
	}
}

void	add_before(t_token **tokens, t_token *current, t_token *new)
{
	t_token	*tmp;

	if (!tokens || !current || !new)
		return ;
	if (current->prev)
	{
		tmp = current->prev;
		new->next = current;
		current->prev = new;
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*tokens = new;
		current->prev = new;
		new->next = current;
	}
}

void	add_after(t_token *current, t_token *new)
{
	t_token	*tmp;

	if (!current || !new)
		return ;
	if (current->next)
	{
		tmp = current->next;
		current->next = new;
		new->prev = current;
		new->next = tmp;
		tmp->prev = new;
	}
	else
	{
		current->next = new;
		new->prev = current;
	}
}

/*
 * splits next token string at split_index
 * appends a new token in between
 * ex : "<" "infile cat -e" becomes "<" "infile" "cat -e"
 */
void	split_append_token(t_data *data, t_token *token, int split_index, \
		t_tokentype filetype)
{
	char	*filepath;
	char	*string2;
	t_token	*new;

	filepath = ft_substr(token->next->string, 0, split_index);
	check_alloc(data, filepath);
	new = new_token(data, filetype, token->index, "");
	check_alloc(data, new);
	free(new->string);
	new->string = filepath;
	string2 = ft_substr(token->next->string, split_index + 1, \
		ft_strlen(token->next->string));
	check_alloc(data, string2);
	free(token->next->string);
	token->next->string = string2;
	add_after(token, new);
}
