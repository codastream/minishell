#include "shell.h"

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
			check_closing_quotes(line);
			printf("%s\n", line);
			if (!ft_strcmp(line, "exit") || !line)
				break;
			tokens = tokenize(line);
			printf("\n%safter tokenize%s\n", P_PINK, P_NOC);
			print_tokens(tokens);
			do_for_tokens(tokens, merge_word_with_next_literal);
			do_for_tokens(tokens, check_redirection);
			printf("\n%safter check redir%s\n", P_PINK, P_NOC);
			print_tokens(tokens);
			do_for_tokens(tokens, check_pipe);
			printf("\n%safter check pipe%s\n", P_PINK, P_NOC);
			print_tokens(tokens);
			free_tokens(tokens);
			free(prompt);
			free(line);
		}
	free (prompt);
	}
	else
		printerr("launch ./minishell without option\n");
}
