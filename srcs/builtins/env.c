#include "shell.h"

void	ft_env(t_data *data, t_token *token)
{
	int			i;
	t_keyval	**keyvals;
	t_keyval	*current;
	t_hash		*hash;

	(void) token;
	hash = data->localvars;
	keyvals = hash->keyvals;
	i = 0;
	if (token->command->command_args[1] && ft_strcmp(token->command->command_args[1], "env"))
	{
		handle_custom_error_source_builtin(data, token->command->command_name, \
		MSG_USAGE_NO_OPTS_NO_ARGS, EXIT_SYNTAX_ERROR);
		return ;
	}
	while (i < hash->capacity)
	{
		if (keyvals[i++])
		{
			current = keyvals[i - 1];
			while (current)
			{
				if (current->value && ft_strcmp(current->key, LAST_RETURN_CODE))
					ft_printfd(token->out, "%s=%s\n", current->key, \
					current->value);
				current = current->next;
			}
		}
	}
	update_last_return(data, EXIT_SUCCESS);
}
