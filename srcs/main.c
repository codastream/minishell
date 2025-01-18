#include "../includes/shell.h"

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) env;
	if (ac == 1)
	{
		printf("Hello");
	}
	else
	{
		printerr("launch ./minishell without option\n");
	}
}
