/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:11:52 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:53:28 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_fd(t_data *data, t_exec *exec)
{
	(void) data;
	printf("\t---fds\n");
	printf("\tcommand # %d\n", exec->current_cmd_index);
	printf("\tfds read end %d\n", exec->fds[0]);
	printf("\tfds write end %d\n", exec->fds[1]);
	printf("\t---\n");
}

static void	print_redir(t_redir *redir)
{
	printf("\t\t%s%s : %s%s\n", P_GREEN, get_token_type(redir->type), \
		redir->string, P_NOC);
}

static void	print_redirs(t_list *redirlist)
{
	t_list	*current;

	current = redirlist;
	while (current)
	{
		print_redir((t_redir *) current->content);
		current = current->next;
	}
	printf("\n");
}

static void	print_command(t_command *command)
{
	int	i;

	printf("\t\t%scommand name\t:%s%s\n", P_PINK, command->command_name, P_NOC);
	printf("\t\t%sargs\t\t:%s", P_PINK, P_NOC);
	if (command->command_args)
	{
		i = 0;
		while (command->command_args[i])
		{
			printf("%s%s|%s", P_PINK, command->command_args[i], P_NOC);
			i++;
		}
	}
	printf("\n");
}

void	print_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		printf("token #%d\t", current->index);
		printf("%s%*s%s", P_BLUE, 21, current->string, P_NOC);
		printf("\t\ttype %s\n", get_token_type(current->type));
		if (current->type == T_COMMAND)
		{
			print_redirs(current->command->redirections);
			print_command(current->command);
		}
		current = current->next;
	}
	printf("\n");
}
