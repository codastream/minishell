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
			data->line = readline((const char*)data->prompt);
			if (data->line)
				add_history(data->line);
			code = check_closing_quotes(data, data->line);
			if (code != EXIT_SUCCESS)
				continue ;
			code = tokenize(data, data->line);
			if (code != EXIT_SUCCESS)
				continue ;
			tree = make_tree(*(data->tokens));
			check_alloc(data, tree);
			data->tree = tree;
			code = exec_line(data, data->tree);
			update_last_return(data, code);
			free_after_exec(data);
		}
		ft_free_hashtable(data->vars);
		free_data(data);
		return (code);
	}
	else
		printerr("launch ./minishell without option\n");
}
