#include "../includes/shell.h"

int	main(int ac, char **av, char **env)
{
	char				*line;

	(void) av;
	(void) env;
	if (ac == 1)
	{
		setup_signal();
		while (1)
		{
			line = readline("\001\033[36;1m\002C_Shell > \001\033[0m\002");
			if (!ft_strcmp(line, "exit") || !line)	// condition a rectifier
				break;
			ft_printf("%s\n", line);	// la ou appeler la fonction parsing et faire l'execution
			free (line);
		}
	}
	else
	{
		printerr("launch ./minishell without option\n");
	}
}
