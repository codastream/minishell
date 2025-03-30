/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_custom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:09:19 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/30 18:48:40 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handle_end_of_loop(t_data *data)
{
	int	code;

	if (isatty(STDIN_FILENO))
		printf("exit\n");
	code = get_last_return(data);
	free(data->prompt);
	free_vars_and_data(data);
	exit(code);
}

void	handle_non_interactive_end(t_data *data, char *step)
{
	int	code;

	code = get_last_return(data);
	if (PRINT == 1)
		printf("handle noninter end code %d\n", code);
	if (!ft_strcmp(step, "beforeexec"))
	{
		free_vars_and_data(data);
		rl_clear_history();
	}
	else if (!ft_strcmp(step, "afterexec"))
	{
		free_all_data(data);
	}
	exit(code);
}

void	handle_quote_error(t_data *data)
{
	printerr(MSG_SYNTAX_QUOTE_ERROR);
	update_last_error(data, EXIT_SYNTAX_ERROR);
	free_before_parsing(data);
}

void	handle_syntax_error(t_data *data, char *token_str)
{
	printerr_syntax(token_str);
	update_last_error(data, EXIT_SYNTAX_ERROR);
	free_after_parsing(data);
}

void	check_alloc(t_data *data, void *allocated)
{
	if (!allocated)
		handle_custom_error(data, MSG_MEMORY_ERROR, EXIT_FAILURE, true);
}
