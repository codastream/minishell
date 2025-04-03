/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:59:17 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 19:01:11 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_command	*new_command(t_data *data, char *string)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	check_alloc(data, command);
	if (string && string[0] != '\0')
		update_command_from_string(data, command, string);
	else
	{
		command->command_name = NULL;
		command->command_args = NULL;
	}
	command->has_invalid_redir = false;
	return (command);
}

int	update_command_from_extra_words_before_pipe(t_data *data, \
		t_token **tokens, t_token *token)
{
	t_token	*current;
	char	*elems[2];
	char	*joined;
	t_token	*tmp;

	if (!token->next || (token->type != T_COMMAND && token->type != T_WORD))
		return (EXIT_IGNORE);
	current = token->next;
	while (current && current->type != T_PIPE)
	{
		tmp = current->next;
		if (current->type == T_WORD)
		{
			elems[0] = token->string;
			elems[1] = current->string;
			joined = ft_multistrjoin(2, elems, " ");
			check_alloc(data, joined);
			free(token->string);
			token->string = joined;
			delete_token(tokens, current);
		}
		current = tmp;
	}
	return (EXIT_SUCCESS);
}

void	add_command_to_token(t_data *data, t_token **tokens, \
	t_token *token)
{
	t_command	*command;

	(void) tokens;
	command = new_command(data, token->string);
	check_alloc(data, command);
	token->command = command;
	token->type = T_COMMAND;
}

t_token	*remove_extra_command(t_data *data, t_token **tokens, \
	t_token *token, t_token *next)
{
	t_token	*tmp;

	(void) data;
	(void) next;
	if (token->type != T_COMMAND)
		return (token->next);
	if (token->next && token->next->type == T_COMMAND)
	{
		tmp = token->next->next;
		delete_token(tokens, token->next);
		return (tmp);
	}
	return (token->next);
}
