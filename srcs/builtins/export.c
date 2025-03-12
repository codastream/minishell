#include "shell.h"

int	ft_strndup(char **var, char *cmd, int start, int end)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_calloc(end - start + 1, sizeof(char));
	if (!result)
		return (0);
	while (cmd[start] && start != end)
		result[i++] = cmd[start++];
	*var = result;
	return (1);
}

char	**split_export_cmd(char *cmd)
{
	int		i;
	int		j;
	int		code;
	char	**result;

	i = 0;
	result = ft_calloc(4, sizeof(char *));
	if (!result)
		return (NULL);
	while (ft_isalnum(cmd[i]))
		i++;
	code = ft_strndup(&result[0], cmd, 0, i);
	if (!code)
		return (NULL);
	j = i;
	while (cmd[i] && cmd[i - 1] != '=')
		i++;
	code = ft_strndup(&result[1], cmd, j, i);
	if (!code)
		return (NULL);
	code = ft_strndup(&result[2], cmd, i, ft_strlen(cmd));
	return (result);
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
		handle_custom_error_source_exit(data, token->command->command_name, \
		MSG_USAGE_NO_OPTS_NO_ARGS, EXIT_SYNTAX_ERROR);
	while (i < hash->capacity)
	{
		if (keyvals[i])
		{
			current = keyvals[i];
			while (current)
			{
				ft_printfd(token->out, "declare -x %s=\"%s\"\n", current->key, \
					current->value);
				current = current->next;
			}
		}
		i++;
	}
}

void	pars_export(t_data *data, t_token *token, int i)
{
	char	**cmd;

	cmd = split_export_cmd(token->command->command_args[i]);
	if (ft_isalpha(cmd[0][0]) && !ft_strcmp(cmd[1], "+="))
		append_export(data, cmd);
	else if (ft_isalpha(cmd[0][0]) && !ft_strcmp(cmd[1], "="))
		supress_export(data, cmd);
	else if (ft_isalpha(cmd[0][0]) && !cmd[1][0])
		ft_hash_insert(data->expvars, cmd[0], NULL);
	else
	{
		ft_printfd(2, "export: `%s%s%s': not a valid identifier\n", \
		cmd[0], cmd[1], cmd[2]);
		ft_hash_update(data->vars, LAST_RETURN_CODE, "1");
	}
	ft_free_2d_char_null_ended(cmd);
}

void	ft_export(t_data *data, t_token *token)
{
	int		i;

	i = 1;
	if (!token->command->command_args[1])
	{
		ft_print_export(data, token);
		return ;
	}
	while (token->command->command_args[i])
		pars_export(data, token, i++);
}
