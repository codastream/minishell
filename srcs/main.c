#include "shell.h"


bool	is_empty_line(char *prompt)
{
	if (!prompt)
		return (true);
	while (*prompt && *prompt == ' ')
		prompt++;
	if (!*prompt)
		return (true);
	return (false);
}

int	prepare_exit(t_data *data)
{
	int	code;

	code = data->return_code;
	free(data->prompt);
	free_vars_and_data(data);
	return (code);
}

int	prepare_exit_exec(t_data *data)
{
	int	code;

	if (data->tokens)
		free(data->tokens);
	if (data->tree)
		free_tree(data->tree);
	if (data->exec)
		free_exec(data->exec);
	if (data->line)
		free(data->line);
	code = ft_atoi(ft_hash_get(data->vars, LAST_RETURN_CODE));
	free(data->prompt);
	free_vars_and_data(data);
	return (code);
}

void	process_line_input_non_interactive(t_data *data)
{
	int	code;
	int len;

	data->line = get_next_line(STDIN_FILENO);
	len = ft_strlen(data->line);
	data->line[len - 1] = '\0';
	if (!data->line)
	{
		exit(prepare_exit(data));
	}
	// printf("after get - |%s|\n", data->line);
	code = check_closing_quotes(data, data->line);
	if (code != EXIT_SUCCESS)
		exit(prepare_exit(data));
	code = tokenize(data, data->line);
	if (code != EXIT_SUCCESS)
	{
		exit(prepare_exit(data));
	}
	data->tree = make_tree(*(data->tokens));
	check_alloc(data, data->tree);
	// print_pretty_tree(data, data->tree, 0, "bef exec", false);
	code = exec_line(data, data->tree);
	update_last_return(data, code);
	if (code != EXIT_SUCCESS)
	{
		exit(prepare_exit_exec(data));
	}
	if (PRINT == 1)
	{
		ft_put_green("after exec_line\n");
		printf("code from exec %s%d%s\n", P_PINK, code, P_NOC);
	}
	free_after_exec(data);
	exit(prepare_exit(data));
}

int	empty_line(char *prompt)
{
	if (!prompt)
		return (0);
	while (*prompt && *prompt == ' ')
		prompt++;
	if (!*prompt)
		return (0);
	return (1);
}

void	process_line_input_interactive(t_data *data)
{
	int code;

	while (true)
	{
		rl_outstream = stderr;
		update_prompt(data);
		data->line = readline((const char *)data->prompt);
		if (!data->line)
			exit(prepare_exit(data));
		if (empty_line(data->line))
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
			data->tree = make_tree(*(data->tokens));
			if (PRINT == 1)
				print_pretty_tree(data, data->tree, 0, "after build tree", false);
			check_alloc(data, data->tree);
			code = exec_line(data, data->tree);
			if (PRINT == 1)
			{
				ft_put_green("after exec_line\n");
				printf("code from exec %s%d%s\n", P_PINK, code, P_NOC);
			}
			update_last_return(data, code);
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
