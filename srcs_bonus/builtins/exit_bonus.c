/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:30:51 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:54:53 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_return_code(t_data *data, t_token *token)
{
	int		return_code;
	char	*msg;

	if (is_atoll_str(token->command->command_args[1]))
		return_code = ft_atoll(token->command->command_args[1]) % 256;
	else
	{
		msg = build_wrongvar_msg(data, token->command->command_name, \
		token->command->command_args[1], "numeric argument required");
		handle_custom_error(data, msg, EXIT_SYNTAX_ERROR, false);
		return_code = 2;
		free(msg);
	}
	return (return_code);
}

void	ft_exit(t_data *data, t_token *token)
{
	int		return_code;
	int		arg_count;

	arg_count = ft_count_2dchar_null_ended(token->command->command_args);
	return_code = get_last_return(data);
	if (token->command->command_args[1])
		return_code = handle_return_code(data, token);
	if (arg_count > 2 && return_code != 2)
	{
		handle_custom_error_source_builtin(data, token->command->command_name, \
		MSG_TOO_MANY_ARGUMENTS, EXIT_FAILURE);
		return ;
	}
	if (!data->tree->left && !data->tree->right)
		ft_printfd(2, "exit\n");
	free_all_data(data);
	exit(return_code);
}
