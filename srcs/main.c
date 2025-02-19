#include "shell.h"

void	read_input(t_data *data)
{
	if (isatty(STDIN_FILENO))
	{
		rl_outstream = stderr;
		update_prompt(data);
		data->line = readline((const char *)data->prompt);
		// ft_put_green("after prompt\n");
		// printf("line = %s", data->line);
	}
	else
	{
		data->line = get_next_line(STDIN_FILENO);
	}
}

void	process_line_input(t_data *data)
{
	int code;

	while (true)
	{
		read_input(data);
		if (data->line)
			add_history(data->line);
		else
		{
			// printf("no data->line\n");
			code = data->return_code;
			free(data->prompt);
			free_data(data);
			exit(code);
		}
		// ft_put_green("after add history\n");
		code = check_closing_quotes(data, data->line);
		if (code != EXIT_SUCCESS)
			continue ;
		code = tokenize(data, data->line);
		if (code != EXIT_SUCCESS)
			continue ;
		// ft_put_green("after tokenize\n");
		data->tree = make_tree(*(data->tokens));
		check_alloc(data, data->tree);
		code = exec_line(data, data->tree);
		// ft_put_green("after exec_line\n");
		// printf("code from exec %s%d%s\n", P_PINK, code, P_NOC);
		update_last_return(data, code);
		free_after_exec(data);
	}
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
