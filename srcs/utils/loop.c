/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:09:05 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/10 20:30:18 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "shell.h"

extern int	g_signal;

char	*adjust_color_to_last_return(t_data *data)
{
	int	last_return;

	last_return = get_last_return(data);
	if (last_return == 0)
		return (P_GREEN_PROMPT);
	else
		return (P_RED_PROMPT);
}

/*
 * generates prompt string with format $USERNAME@shellname>
 */
void	update_prompt(t_data *data)
{
	char	*username;
	char	**elems;
	char	*prompt;
	char	*wd;

	username = getenv("USER");
	if (!username)
		username = "user";
	wd = ft_hash_get(data->localvars, "PWD");
	elems = ft_calloc(10, sizeof(char *));
	check_alloc(data, elems);
	elems[0] = P_TEAL_BOLD_PROMPT;
	elems[1] = username;
	elems[2] = P_TEAL_LIGHT_PROMPT;
	elems[3] = "@cshell ";
	elems[4] = P_PINK_PROMPT;
	elems[5] = wd;
	elems[6] = adjust_color_to_last_return(data);
	elems[7] = " ▶ ";
	elems[8] = P_NOC_PROMPT;
	elems[9] = NULL;
	prompt = ft_multistrjoin(9, elems, "");
	free(elems);
	check_alloc(data, prompt);
	data->prompt = prompt;
}

static void	process_line_input_non_interactive(t_data *data)
{
	int	code;

	rl_outstream = stderr;
	if (!isatty(0))
		rl_prep_term_function = 0;
	data->line = readline(NULL);
	if (PRINT == 1)
		printf("line -> %s\n", data->line);
	if (!data->line)
		handle_end_of_loop(data);
	if (!is_empty_line(data->line))
	{
		code = check_closing_quotes(data, data->line);
		if (code != EXIT_SUCCESS)
			handle_non_interactive_end(data, "beforeexec");
		code = tokenize(data, data->line);
		if (PRINT == 1)
			printf("code from tokenize = %d\n", code);
		if (code != EXIT_SUCCESS)
			handle_non_interactive_end(data, "beforeexec");
		data->tree = make_tree(data, *(data->tokens));
		check_alloc(data, data->tree);
		exec_line(data, data->tree);
	}
	handle_non_interactive_end(data, "afterexec");
}

static void	process_line_input_interactive(t_data *data)
{
	int	code;

	while (true)
	{
		rl_outstream = stderr;
		update_prompt(data);
		data->line = readline((const char *)data->prompt);
		check_signal_ok(data);
		if (!is_empty_line(data->line))
		{
			add_history(data->line);
			code = check_closing_quotes(data, data->line);
			if (code != EXIT_SUCCESS)
				continue ;
			code = tokenize(data, data->line);
			if (code != EXIT_SUCCESS)
				continue ;
			if (PRINT == 1)
				ft_put_green("after tokenize\n");
			data->tree = make_tree(data, *(data->tokens));
			check_alloc(data, data->tree);
			exec_line(data, data->tree);
		}
		free_after_exec(data);
	}
}

void	process_line_input(t_data *data)
{
	if (isatty(STDIN_FILENO))
		process_line_input_interactive(data);
	else
		process_line_input_non_interactive(data);
}
