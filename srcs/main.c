#include "../includes/shell.h"

void handle_sigint(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa;
	char				*line;

	(void) av;
	(void) env;
	if (ac == 1)
	{
		sa.sa_handler = handle_sigint;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		while (true)
		{
			line = readline("\001\033[36;1m\002C_Shell > \001\033[0m\002");
			if (!ft_strncmp(line, "exit", 3) || !line)
				break;
			ft_printf("%s\n", line);
			free (line);
		}
	}
	else
	{
		printerr("launch ./minishell without option\n");
	}
}
