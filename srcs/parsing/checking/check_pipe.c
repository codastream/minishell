/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:16:47 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/29 09:27:07 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_command *new_command(char *string)
{
	char 		**name_with_args;
	t_command	*command;

	name_with_args = ft_split(string, ' ');
	check_alloc(name_with_args);
	command = ft_calloc(1, sizeof(t_command));
	check_alloc(command);
	command->command_args = name_with_args;
	return (command);
}

void	add_command_to_token(t_token *token, bool is_before_pipe)
{
	t_command	*command;

	if (is_before_pipe)
		token = get_first_of_consecutive(token);
	while (token->next->type == token->type)
		merge_with_next(token);
	command = new_command(token->string);
	token->command = command;
	token->type = T_COMMAND;
}

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
	if (token->prev->type == T_WORD)
		add_command_to_token(token->prev, true);
	else if (token->prev->type != T_FILE)
		handle_syntax_error(token->string);
	if (token->next->type == T_WORD)
		add_command_to_token(token->next, false);
	else if (token->next->type != T_REDIR_OUT && token->next->type != T_REDIR_APPEND)
		handle_syntax_error(token->next->string);
}
