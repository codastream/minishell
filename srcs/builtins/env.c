#include "shell.h"

void	ft_env(t_data *data, t_token *token)
{
	int			i;
	t_keyval	**keyvals;
	t_keyval	*current;
	t_hash		*hash;

	(void) token;
	hash = data->vars;
	keyvals = hash->keyvals;
	i = 0;
	if (token->command->command_args[1])
		handle_builtin_error(data, token->command, \
		"usage : no OPTS and no ARGS", EXIT_SYNTAX_ERROR);
	while (i < hash->capacity)
	{
		if (keyvals[i++])
		{
			current = keyvals[i - 1];
			while (current)
			{
				ft_printfd(token->out, "%s=%s\n", current->key, \
					current->value);
				current = current->next;
			}
		}
	}
}
