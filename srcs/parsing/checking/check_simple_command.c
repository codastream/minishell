#include "shell.h"

char	*find_in_paths(t_data *data, char **splitted_paths, char *name)
{
	int		i;
	char	*pathname;
	char	*path_elems[2];

	i = 0;
	while (splitted_paths[i])
	{
		path_elems[0] = splitted_paths[i];
		path_elems[1] = name;
		pathname = ft_multistrjoin(2, path_elems, "/");
		check_alloc(data, pathname);
		if (access(pathname, X_OK) == 0)
			break ;
		free(pathname);
		pathname = NULL;
		i++;
	}
	return (pathname);
}

char	*get_checked_pathmame(t_data *data, t_command *command)
{
	char		*path;
	char		**splitted_paths;
	char		*pathname;

	if (access(command->command_name, X_OK) == 0)
		return (ft_strdup(command->command_name));
	path = ft_hash_get(data->vars, "PATH");
	if (!path)
		return (NULL);
	splitted_paths = ft_split(path, ':');
	check_alloc(data, splitted_paths);
	// if (ft_strlen(command->command_name) == 0)
	// 	return (NULL);
	pathname = find_in_paths(data, splitted_paths, command->command_name);
	ft_free_2d_char_null_ended(splitted_paths);
	return (pathname);
}

void	add_simple_command_to_token(t_data *data, t_token **tokens, t_token *token)
{
	t_command	*command;

	if (token->type != T_WORD)
		return ;
	while (token->next && token->next->type == T_WORD)
		merge_with_next(data, tokens, token);
	command = new_command(data, token->string);
	token->command = command;
	token->type = T_COMMAND;
	add_previous_redirect_to_command(data, tokens, token);
	add_following_redirect_to_command(data, tokens, token);
}

int	merge_word_with_next_words_and_make_command(t_data *data, t_token **tokens, t_token *token)
{
	if (token->type == T_WORD)
		add_simple_command_to_token(data, tokens, token);
	else
		return (EXIT_IGNORE);
	return (EXIT_SUCCESS);
}
