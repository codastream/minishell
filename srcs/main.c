#include "../includes/shell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;
	t_token **tokens;

	(void) av;
	(void) env;
	if (ac == 1)
	{
		setup_signal();
		prompt = NULL;
		while (true)
		{
			prompt = update_prompt();
			line = readline((const char*)prompt);
			printf("%s\n", line);
			if (!ft_strcmp(line, "exit") || !line)
				break;
			tokens = tokenize(line);
			print_tokens(tokens);
			do_for_tokens(tokens, check_redirection);
			free_tokens(tokens);
			free(prompt);
			free(line);
		}
	free (prompt);
	}
	else
		printerr("launch ./minishell without option\n");
}
