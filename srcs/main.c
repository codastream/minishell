#include "shell.h"

int	main(int ac, char **av, char **env)
{
	t_tree	*tree;
	int		code;
	t_data	*data;

	(void) av;
	if (ac == 1)
	{
		setup_signal();
		data = init_data(env);
		if (!data)
			return (EXIT_FAILURE);
		while (true)
		{
			update_prompt(data);
			// ft_put_green("after prompt\n");
			rl_outstream = stderr;
			data->line = readline((const char*)data->prompt);
			// printf("line = %s", data->line);
			if (data->line)
			{
				add_history(data->line);
			}
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
			tree = make_tree(*(data->tokens));
			check_alloc(data, tree);
			data->tree = tree;
			code = exec_line(data, data->tree);
			// ft_put_green("after exec_line\n");
			// printf("code from exec %s%d%s\n", P_PINK, code, P_NOC);
			update_last_return(data, code);
			free_after_exec(data);
		}
	}
	else
		printerr("launch ./minishell without option\n");
	return (EXIT_SUCCESS);
}
