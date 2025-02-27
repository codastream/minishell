#include "shell.h"

bool	is_empty_line(char *line)
{
	if (!line)
		return (true);
	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (true);
	return (false);
}

void	process_line_input_non_interactive(t_data *data)
{
	int	code;
	int len;

	data->line = get_next_line(STDIN_FILENO);
	len = ft_strlen(data->line);
	data->line[len - 1] = '\0';
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

void	process_line_input(t_data *data)
{
	int code;

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
			if (PRINT == 1)
				print_pretty_tree(data, data->tree, 0, "after build tree", false);
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

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void) av;
	if (ac == 1)
	{
		setup_signal();
		data = init_data(env);
		if (!data)
			return (EXIT_FAILURE);
		process_line_input(data);
	}
	else
		printerr("launch ./minishell without option\n");
	return (EXIT_SUCCESS);
}
