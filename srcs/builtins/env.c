/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:15 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/09 19:43:44 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	check_print(t_keyval *current, t_token *token)
{
	if (!current->value)
		return ;
	if (current->value && \
		ft_strcmp(current->key, LAST_RETURN_CODE))
		ft_printfd(token->out, "%s=%s\n", current->key, \
		current->value);
	else if (!current->value[0] && ft_strcmp(current->key, LAST_RETURN_CODE))
		ft_printfd(token->out, "%s=\n", current->key, \
		current->value);
}

static void	print_envvar(t_data *data, t_token *token)
{
	t_keyval	*current;
	t_keyval	**keyvals;
	t_hash		*hash;
	int			i;

	i = 0;
	hash = data->localvars;
	keyvals = hash->keyvals;
	while (i < hash->capacity)
	{
		if (keyvals[i])
		{
			current = keyvals[i];
			while (current)
			{
				check_print(current, token);
				current = current->next;
			}
		}
		i++;
	}
}

void	ft_env(t_data *data, t_token *token)
{
	if (token->command->command_args[1] && \
		ft_strcmp(token->command->command_args[1], "env"))
	{
		handle_custom_error_source_builtin(data, token->command->command_name, \
			MSG_USAGE_NO_OPTS_NO_ARGS, EXIT_SYNTAX_ERROR);
		return ;
	}
	print_envvar(data, token);
	update_last_return(data, EXIT_SUCCESS);
}
