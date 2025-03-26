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
	char	*trimmed;

	i = 0;
	result = ft_calloc(4, sizeof(char *));
	if (!result)
		return (NULL);
	while (ft_ischarforenvvar(cmd[i]))
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
	if (result[2][i] == '\'' && result[2][ft_strlen(result[2]) - 1] == '\'')
	{
		trimmed = ft_strtrim(result[2], "'");
		free(result[2]);
		result[2] = trimmed;
	}
	return (result);
}

void	ft_print_export(t_data *data, t_token *token)
{
	int			i;
	t_keyval	**keyvals;
	t_keyval	*current;
	t_hash		*hash;

	hash = data->localvars;
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
				if (current->value)
					ft_printfd(token->out, "declare -x %s=\"%s\"\n", current->key, \
					current->value);
				else
					ft_printfd(token->out, "declare -x %s\n", current->key);
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
	if (ft_isenvvarkeystr(cmd[0]) && !ft_strcmp(cmd[1], "+="))
		append_export(data, cmd);
	else if (ft_isenvvarkeystr(cmd[0]) && !ft_strcmp(cmd[1], "="))
		supress_export(data, cmd);
	else if (ft_isenvvarkeystr(cmd[0]) && !cmd[1][0])
		ft_hash_insert(data->expvars, cmd[0], NULL);
	else if (token->command->command_args[i][0] == '-')
		update_last_return(data, EXIT_SYNTAX_ERROR);
	else
	{
		ft_printfd(2, "export: `%s%s%s': not a valid identifier\n", \
			cmd[0], cmd[1], cmd[2]);
		update_last_return(data, EXIT_FAILURE);
	}
	ft_free_2d_char_null_ended(cmd);
}

bool	is_valid_identifier(char *arg)
{
	if (!arg)
		return (false);
	if (arg[0] == '=')
		return (false);
	return (true);
}

void	ft_export(t_data *data, t_token *token)
{
	int		i;

	update_last_return(data, EXIT_SUCCESS);
	if (!token->command->command_args[1])
	{
		ft_print_export(data, token);
		return ;
	}
	i = 1;
	while (token->command->command_args[i])
	{
		if (!is_valid_identifier(token->command->command_args[i]))
		{
			ft_printfd(2, "export: `%s': not a valid identifier\n", token->command->command_args[i]);
			update_last_return(data, 1);
			break ;
		}
		pars_export(data, token, i++);
	}
}
