#include "shell.h"

char **init_separators(void)
{
	char		**separators;

	separators = ft_calloc(7, sizeof(char *));
	check_alloc(separators);
	separators[0] = " ";
	separators[1] = "|";
	separators[2] = "<<";
	separators[3] = "<";
	separators[4] = ">>";
	separators[5] = ">";
	separators[6] = NULL;
	return (separators);
}

static void	add_token(t_token **tokens, char *s, int i)
{
	t_token		*token;

	if (ft_isemptystr(s))
		return ;
	else if (s[0] == '"')
		token = new_token(T_LITERAL_DOUBLE, i, s);
	else if (s[0] == '\'')
		token = new_token(T_LITERAL_SINGLE, i, s);
	else if (!ft_strcmp(s, "|"))
		token = new_token(T_PIPE, i, s);
	else if (!ft_strcmp(s, "<<"))
		token = new_token(T_REDIR_HEREDOC, i, s);
	else if (!ft_strcmp(s, "<"))
		token = new_token(T_REDIR_IN, i, s);
	else if (!ft_strcmp(s, ">>"))
		token = new_token(T_REDIR_APPEND, i, s);
	else if (!ft_strcmp(s, ">"))
		token = new_token(T_REDIR_OUT, i, s);
	else
		token = new_token(T_WORD, i, s);
	add_token_back(tokens, token);
}

void	do_for_tokens(t_token **tokens, void (*f)(t_token *))
{
	t_token	*current;

	if (!tokens)
		return ;
	current = *tokens;
	while (current)
	{
		f(current);
		current = current->next;
	}
}

/*
 * called after syntax check
 * splits and assigns first labels (ie enums) to input parts
 */
t_token	**tokenize(char *line)
{
	char		**separators;
	char		**splitted;
	int			i;
	t_token 	**tokens;

	tokens = ft_calloc(1, sizeof(t_token *));
	check_alloc(tokens);
	separators = init_separators();
	check_alloc(separators);
	splitted = ft_split_skip(line, separators);
	check_alloc(splitted);
	i = 0;
	while (splitted[i])
	{
		add_token(tokens, splitted[i], i);
		i++;
	}
	ft_free_2d_char_null_ended(splitted);
	free(separators);
	return(tokens);
}
