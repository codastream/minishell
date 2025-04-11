/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:14:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 22:43:39 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->command_args)
		ft_free_2d_char_null_ended(command->command_args);
	if (command->command_name)
		reset(command->command_name);
	if (command->pathname)
		reset(command->pathname);
	if (command->redirections)
	{
		ft_lstiter(command->redirections, free_redir_list);
		ft_lstclear(&command->redirections, free);
	}
	reset(command);
}

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->builtins)
		free(exec->builtins);
	if (exec->builtin_ptrs)
		free(exec->builtin_ptrs);
	if (exec->error_msg)
		free(exec->error_msg);
	reset(exec);
}

void	free_token(t_token *token)
{
	if (token->command)
		free_command(token->command);
	if (token->string)
		reset(token->string);
	reset(token);
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*tmp;

	if (!tokens)
		return ;
	if (*tokens)
	{
		current = tokens[0];
		while (current)
		{
			tmp = current->next;
			free_token(current);
			current = tmp;
		}
	}
	reset(tokens);
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->right)
		free_tree(tree->right);
	if (tree->left)
		free_tree(tree->left);
	free_token(tree->value);
	reset(tree);
}
