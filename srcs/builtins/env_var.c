#include "shell.h"

int	ft_strndup(char **var, char *cmd, int start, int end)
{
	int	  i;
	char  *result;

	i = 0;
	result = ft_calloc(end - start + 1, sizeof(char));
	if (!result)
		return (0);
	while (cmd[start] && start != end)
		result[i++] = cmd[start++];
	*var = result;
//	printf("-> %s\n", result);
	return (1);
}

char  **split_export_cmd(char *cmd)
{
	int	  i;
	int	  j;
	int	  code;
	char  **result;

	i = 0;
	result = ft_calloc(4, sizeof(char *));
	if (!result)
		return (NULL); //tmp
	while (ft_isalnum(cmd[i]))
		i++;
	code = ft_strndup(&result[0], cmd, 0, i);
	if (!code)
		return (NULL); //tmp
	j = i;
	while (cmd[i] && cmd[i - 1] != '=')
		i++;
	code = ft_strndup(&result[1], cmd, j, i);
	if (!code)
		return (NULL); //tmp
	code = ft_strndup(&result[2], cmd, i, ft_strlen(cmd));
//	printf("%s - %s -%s\n", result[0], result[1], result[2]);
	return (result);
}

void  append_export(t_data *data, char **cmd)
{
	char *result;

	result = ft_hash_get(data->vars, cmd[0]);
	if (!result)
	{
		ft_hash_insert(data->vars, cmd[0], cmd[2]);
		ft_hash_insert(data->vars, cmd[0], cmd[2]);
	}
	else
	{
		result = ft_strjoin(result, cmd[2]);
		ft_hash_update(data->vars, cmd[0], result);
		ft_hash_update(data->expvars, cmd[0], result);
		free(result);
	}
}

void  supress_export(t_data *data, char **cmd)
{
	ft_hash_remove(data->vars, cmd[0]);
	ft_hash_insert(data->vars, cmd[0], cmd[2]);
	ft_hash_remove(data->expvars, cmd[0]);
	if (!cmd[2][0])
		ft_hash_insert(data->expvars, cmd[0], "\"\"");
	else
		ft_hash_insert(data->expvars, cmd[0], cmd[2]);
}

void	ft_print_export(t_data *data, t_token *token)
{
	int			i;
	t_keyval	**keyvals;
	t_keyval	*current;
	t_hash		*hash;

	hash = data->expvars;
	keyvals = hash->keyvals;
	i = 0;
	if (token->command->command_args[1])
		handle_builtin_error(data, token->command, "usage : no OPTS and no ARGS", EXIT_SYNTAX_ERROR);
	while (i < hash->capacity)
	{
		if (keyvals[i])
		{
			current = keyvals[i];
			while (current)
			{
				ft_printfd(token->out, "declare -x %s=%s\n", current->key, \
					(char *) current->value);
				current = current->next;
			}
		}
		i++;
	}
}
