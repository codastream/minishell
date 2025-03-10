#include "shell.h"

static bool	is_empty_line(char *line)
{
	if (!line)
		return (true);
	while (*line && ft_isemptychar(*line))
		line++;
	if (!*line)
		return (true);
	return (false);
}

/*
 * generates prompt string with format $USERNAME@shellname>
 */
void	update_prompt(t_data *data)
{
	char	*username;
	char	**elems;
	char	*prompt;

	username = getenv("USER");
	if (!username)
		username = "user";
	elems = ft_calloc(10, sizeof(char *));
	check_alloc(data, elems);
	elems[0] = P_TEAL_BOLD_PROMPT;
	elems[1] = username;
	elems[2] = P_TEAL_LIGHT_PROMPT;
	elems[3] = "@";
	elems[4] = P_TEAL_BOLD_PROMPT;
	elems[5] = "C_shell";
	elems[6] = P_GREEN_PROMPT;
	elems[7] = " >";
	elems[8] = P_NOC_PROMPT;
	elems[9] = NULL;
	prompt = ft_multistrjoin(9, elems, "");
	check_alloc(data, prompt);
	free(elems);
	data->prompt = prompt;
}

static void	process_line_input_non_interactive(t_data *data)
{
	int	code;
	// int	len;

	rl_outstream = stderr;
	if (!isatty(0))
		rl_prep_term_function = 0;
	data->line = readline(NULL);
	// data->line = get_next_line(STDIN_FILENO);
	// len = ft_strlen(data->line);
	// data->line[len - 1] = '\0';
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
		if (!data->line)
			handle_end_of_loop(data);
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
