#include "../includes/shell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;
	t_alloc	*alloc = NULL;

	(void) av;
	(void) env;
	if (ac == 1)
	{
		setup_signal();
		prompt = update_prompt(&alloc);
		while (1)
		{
			line = readline(prompt);
			if (!ft_strcmp(line, "exit") || !line)	// condition a rectifier
				break;
			ft_printf("%s\n", line);	// la ou appeler la fonction parsing et faire l'execution
			free (line);	// a free car allocation dans readline
		}
	free (prompt);
	}
	else
		printerr("launch ./minishell without option\n");
	free_all_alloc(alloc);
}
