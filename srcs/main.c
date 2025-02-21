#include "shell.h"

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
			rl_outstream = stderr;
			data->line = readline((const char*)data->prompt);
			if (!data->line)
				break ;
			if (empty_line(data->line))
			{
				add_history(data->line);
				check_closing_quotes(data, data->line);
				tokenize(data, data->line);
				tree = make_tree(*(data->tokens));
				check_alloc(data, tree);
				data->tree = tree;
				code = exec_line(data, data->tree);
				pop_all_fd(&data->fds);
			}
			free_after_exec(data);
		}
		free_all_data(data);
	}
	else
		printerr("launch ./minishell without option\n");
	(void)code;
}
