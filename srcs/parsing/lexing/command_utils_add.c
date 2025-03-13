#include "shell.h"

int	update_command_from_extra_words_before_pipe(t_data *data, t_token **tokens, t_token *token)
{
	t_token	*current;
	char	*elems[2];
	char	*joined;
	t_token	*tmp;

	if (!token->next)
		return (EXIT_IGNORE);
	current = token->next;
	while (current && current->type != T_PIPE)
	{
		tmp = current->next;
		if (current->type == T_WORD)
		{
			elems[0] = token->string;
			elems[1] = current->string;
			joined = ft_multistrjoin(2, elems, " ");
			check_alloc(data, joined);
			free(token->string);
			token->string = joined;
			delete_token(tokens, current);
		}
		current = tmp;
	}
	return (EXIT_SUCCESS);
}

void	add_command_to_token(t_data *data, t_token **tokens, \
	t_token *token)
{
	t_command	*command;

	(void) tokens;
	command = new_command(data, token->string);
	check_alloc(data, command);
	token->command = command;
	token->type = T_COMMAND;
}
