/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:59:14 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 22:38:50 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	update_args(t_data *data, t_command *command, char *string)
{
	t_delimiter	**delimiters;
	char		**name_with_args;
	char		**seps;

	seps = ft_calloc(7, sizeof(char *));
	if (!seps)
		free(command);
	check_alloc(data, seps);
	seps[0] = " ";
	seps[1] = "\t";
	seps[2] = "\r";
	seps[3] = "\f";
	seps[4] = "\v";
	seps[5] = "\b";
	seps[6] = NULL;
	delimiters = init_quote_delimiters(data);
	if (!delimiters)
		free(command);
	check_alloc(data, delimiters);
	name_with_args = NULL;
	name_with_args = ft_split_skip(string, seps, delimiters);
	free(seps);
	free_delimiters(delimiters);
	check_alloc(data, name_with_args);
	command->command_args = name_with_args;
}

void	update_command_from_string(t_data *data, t_command *command, \
		char *string)
{
	char	*name;

	if (command->command_args)
		ft_free_2d_char_null_ended(command->command_args);
	if (command->command_name)
		free(command->command_name);
	if (!string || ft_isemptystr(string))
	{
		command->command_args = ft_calloc(1, sizeof(char *));
		command->command_name = ft_calloc(1, sizeof(char));
		return ;
	}
	update_args(data, command, string);
	name = ft_strdup(command->command_args[0]);
	if (!name)
		free_command(command);
	check_alloc(data, name);
	command->command_name = name;
}

t_list	*create_redir(t_data *data, t_token *file_token)
{
	t_list	*new;
	t_redir	*redir;
	char	*redir_file_str;
	bool	has_var;

	has_var = false;
	redir_file_str = get_file_str(data, file_token, &has_var);
	redir = ft_calloc(1, sizeof(t_redir));
	check_alloc(data, redir);
	redir->string = redir_file_str;
	redir->type = file_token->type;
	redir->ambiguous_redir = false;
	redir->has_var = has_var;
	new = ft_calloc(1, sizeof(t_list));
	check_alloc(data, new);
	new->content = redir;
	return (new);
}

void	add_redirect_file_to_command(t_data *data, t_token **tokens, \
	t_token *command_token, t_token *file_token)
{
	t_list	*redir;

	if (PRINT == 1)
	{
		ft_put_yellow("add redirect\n");
		print_tokens(tokens);
	}
	redir = create_redir(data, file_token);
	check_alloc(data, redir);
	ft_lstadd_back(&command_token->command->redirections, redir);
	delete_token(tokens, file_token->prev);
	delete_token(tokens, file_token);
	if (PRINT == 1)
	{
		ft_put_yellow("after add redirect\n");
		print_tokens(tokens);
	}
}
