#include "shell.h"

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
