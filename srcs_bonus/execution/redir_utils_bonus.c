/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:18:38 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:54:13 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	has_redirin(t_tree *tree)
{
	return (tree->value->type == T_COMMAND \
		&& (has_type_of_redir(tree->value->command, T_INFILE) \
			|| has_type_of_redir(tree->value->command, T_EOF)));
}

bool	has_redirout(t_tree *tree)
{
	return (tree->value->type == T_COMMAND \
		&& (has_type_of_redir(tree->value->command, T_OUTFILE_APPEND) \
			|| has_type_of_redir(tree->value->command, T_OUTFILE_TRUNCATE)));
}

bool	has_type_of_redir(t_command *command, t_tokentype type)
{
	t_list	*current;
	t_redir	*redir;

	current = command->redirections;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->type == type)
			return (true);
		current = current->next;
	}
	return (false);
}

bool	is_input_redir(t_redir *redir)
{
	if (!redir)
		return (false);
	return (redir->type == T_INFILE || redir->type == T_EOF);
}

bool	is_output_redir(t_redir *redir)
{
	if (!redir)
		return (false);
	return (redir->type == T_OUTFILE_APPEND || redir->type == T_OUTFILE_APPEND);
}
