#include "shell.h"

int	main(int ac, char **av, char **env)
{
	t_token **tokens;
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
			check_closing_quotes(data, data->line);
			printf("%s\n", data->line);
			tokens = tokenize(data, data->line);
			data->tokens = tokens;
			tree = make_tree(*tokens);
			check_alloc(data, tree);
			data->tree = tree;
			print_pretty_tree(data, data->tree, 0, "root ", false);
			printf("\n");
			code = exec_line(data, data->tree);
			free_after_exec(data);
		}
		ft_free_hashtable(data->vars);
		free_data(data);
	}
	else
		printerr("launch ./minishell without option\n");
	(void)code;
}
