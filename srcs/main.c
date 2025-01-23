#include "../includes/shell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;

	(void) av;
	(void) env;
	if (ac == 1)
	{
		setup_signal();
		prompt = update_prompt();
		while (1)
		{
			line = readline(prompt);
			if (!ft_strcmp(line, "exit") || !line)	// condition a rectifier
				break;
			ft_printf("%i\n", is_quote_ok(line));
			free (line);	// a free car allocation dans readline
		}
	free (prompt);
	}
	else
		printerr("launch ./minishell without option\n");
}
