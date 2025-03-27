/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:59:11 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:59:12 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_previous_redirect_to_command(t_data *data, \
	t_token **tokens, t_token *command_token)
{
	// t_list	**redir_list;
	t_token	*current;
	t_token	*tmp;

	if (PRINT == 1)
		printf("adding previous\n");
	current = command_token;
	while (current && current->prev && current->prev->type != T_PIPE)
		current = current->prev;
	while (current && is_redir_operator(current) && current->next \
		&& is_file(current->next))
	{
		if (current->next->next)
			tmp = current->next->next;
		// redir_list = get_redir_list_from_operator(current, command_token);
		add_redirect_file_to_command(data, tokens, command_token, current->next);
		current = tmp;
	}
	if (PRINT == 1)
		print_tokens(tokens);
}

static void	add_following_redirect_to_command(t_data *data, \
	t_token **tokens, t_token *command_token)
{
	// t_list	**redir_list;

	while (command_token && command_token->next && command_token->next->next \
		&& command_token->next->type != T_PIPE)
	{
		if (is_file(command_token->next->next) \
		&& is_redir_operator(command_token->next))
		{
			// redir_list = get_redir_list_from_operator(command_token->next, command_token);
			add_redirect_file_to_command(data, tokens, command_token, \
				command_token->next->next);
		}
	}
}

static void	add_empty_command_with_redir(t_data *data, \
	t_token **tokens, t_token *token)
{
	t_token	*command_token;

	command_token = new_token(data, T_WORD, token->index, NULL);
	check_alloc(data, command_token);
	add_before(tokens, token, command_token);
	add_command_to_token(data, tokens, command_token);
}

int	add_command_from_word(t_data *data, t_token **tokens, t_token *token)
{
	if (token->type != T_WORD)
		return (EXIT_IGNORE);
	add_command_to_token(data, tokens, token);
	if (PRINT == 1)
		print_tokens(tokens);
	add_previous_redirect_to_command(data, tokens, token);
	if (PRINT == 1)
		print_tokens(tokens);
	add_following_redirect_to_command(data, tokens, token);
	if (PRINT == 1)
		print_tokens(tokens);
	return (EXIT_SUCCESS);
}

t_token	*remove_extra_command(t_data *data, t_token **tokens, t_token *token, t_token *next)
{
	t_token *tmp;

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

t_token	*add_command_from_redirop(t_data *data, t_token **tokens, \
	t_token *token, t_token *next)
{
	t_token	*command_token;
	t_token	*current;

	(void) next;
	if (!is_redir_operator(token))
		return (token->next);
	add_empty_command_with_redir(data, tokens, token);
	command_token = token->prev;
	add_following_redirect_to_command(data, tokens, command_token);
	if (PRINT == 1)
		print_tokens(tokens);
	current = *tokens;
	while (current)
	{
		if (is_redir_operator(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}
