#include "../includes/shell.h"

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) env;
	if (ac == 1)
	{
		char	*prompt;
		char	*line;
		t_token **tokens;

		prompt = NULL;
		while (true)
		{
			prompt = update_prompt();
			line = readline((const char*)prompt);
			printf("%s\n", line);
			tokens = tokenize(line);
			print_tokens(tokens);
			do_for_tokens(tokens, check_redirection);
			free_tokens(tokens);
			free(prompt);
			free(line);
		}
	}
	else
	{
		printerr("launch ./minishell without option\n");
	}
}
