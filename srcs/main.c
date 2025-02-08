#include "shell.h"

// int	main(int ac, char **av, char **env)
// {
// 	t_token **tokens;
// 	t_tree	*tree;
// 	int		code;
// 	t_data	*data;

// 	(void) av;
// 	if (ac == 1)
// 	{
// 		setup_signal();
// 		data = init_data(env);
// 		if (!data)
// 			return (EXIT_FAILURE);
// 		while (true)
// 		{
// 			update_prompt(data);
// 			if (fcntl(STDIN_FILENO, F_GETFL) == -1)
// 					perror("STDIN fermé");
// 			data->line = readline((const char*)data->prompt);
// 			check_closing_quotes(data, data->line);
// 			printf("%s\n", data->line);
// 			if (!ft_strcmp(data->line, "exit"))
// 				break ;
// 			tokens = tokenize(data, data->line);
// 			data->tokens = tokens;
// 			tree = make_tree(*tokens);
// 			check_alloc(data, tree);
// 			data->tree = tree;
// 			print_tree(data->tree);
// 			printf("\n");
// 			code = exec_line(data, data->tree);
// 			free_after_exec(data);
// 		}
// 	}
// 	else
// 		printerr("launch ./minishell without option\n");
// 	(void)code;
// }

int	main(void)
{
	t_data	*data;
	t_tree	*tree;
	t_token	*tokens;

	data = NULL;
	tokens = new_token(data, T_COMMAND, 0, "echo a");

	add_after(tokens, new_token(data, T_PIPE, 1, "|"));
	add_after(tokens->next, new_token(data, T_COMMAND, 2, "ls"));
	tree = make_tree(tokens);
	int	depth;
	depth = ft_tree_get_max_depth(tree);
	printf("depth is %d\n", depth);
}
