#include "shell.h"

bool	ft_isalnumstr(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) == 0)
		return (false);
	while (s[i])
	{
		if (!ft_isalnum(s[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_data *data, t_token *token)
{
	int		return_code;
	int		code;
	int		arg_count;
	char	*msg;

	arg_count = ft_count_2dchar_null_ended(token->command->command_args);
	return_code = EXIT_SUCCESS;
	if (arg_count > 2)
		handle_builtin_error(data, token->command, MSG_TOO_MANY_ARGUMENTS, EXIT_FAILURE);
	if (token->command->command_args[1])
	{
		if (is_atoi_str(token->command->command_args[1]))
		{
			code = ft_atoi(token->command->command_args[1]);
			if (code > 255)
				return_code = EXIT_SYNTAX_ERROR;
			else if (code <= 255)
				return_code = ft_atoi(token->command->command_args[1]);
			else
				return_code = EXIT_FAILURE + ft_atoi(token->command->command_args[1]) % 255;
		}
		else
		{
			msg = build_wrongvar_msg(data, token->command->command_name, token->command->command_args[1], MSG_NUMERIC_ARGUMENT_REQUIRED);
			handle_custom_error(data, msg, EXIT_SYNTAX_ERROR, false);
			return_code = EXIT_SYNTAX_ERROR;
			free(msg);
		}
	}
	free_all_data(data);
	exit(return_code);
}

void	ft_echo(t_data *data, t_token *token)
{
	int		i;
	t_command	*command;

	(void) data;
	i = 1;
	command = token->command;
	if (!(command->command_args)[0])
	return ;
	if (!ft_strcmp((command->command_args)[i], "-n"))
		i++;
	while ((command->command_args)[i])
	{
		ft_printfd(token->out, "%s", (command->command_args)[i]);
		if ((command->command_args)[i + 1])
			ft_printfd(token->out, " ");
		i++;
	}
	if (ft_strcmp((command->command_args)[1], "-n"))
		ft_printfd(token->out, "\n");
}

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
		handle_builtin_error(data, token->command, "usage : no OPTS and no ARGS", EXIT_SYNTAX_ERROR);
	while (i < hash->capacity)
	{
		if (keyvals[i])
		{
			current = keyvals[i];
			while (current)
			{
				ft_printfd(token->out, "%s=%s\n", current->key, \
					(char *) current->value);
				current = current->next;
			}
		}
		i++;
	}
}

char	*getpwd(t_data *data)
{
	int		size;
	char	*buffer;

	size = 2048;
	buffer = malloc(size);
	check_alloc(data, buffer);
	while (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		size = size * 2;
		buffer = malloc(size);
	}
	return (buffer);
}

void	ft_pwd(t_data *data, t_token *token)
{
	int		size;
	char	*buffer;

	(void) data;
	size = 2048;
	buffer = malloc(size);
	check_alloc(data, buffer);
	while (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		size = size * 2;
		buffer = malloc(size);
		check_alloc(data, buffer);
	}
	ft_printfd(token->out, "%s\n", buffer);
	free(buffer);
}

void	ft_cd(t_data *data, t_token *token)
{
	char		*path;
	t_command	*command;

	command = token->command;
	if (command->command_args[2])
	{
		ft_printfd(2, "cd: too many arguments\n");
		ft_hash_update(data->vars, LAST_RETURN_CODE, "1");
		return ;
	}
	if (!(command->command_args)[1])
	{
		chdir(ft_hash_get(data->vars, "HOME"));
		return ; // TODO check leaks and test with free_all_data + exit
	}
	path = ft_joinfree(getpwd(data), "/");
	check_alloc(data, path);
	path = ft_joinfree(path, (command->command_args)[1]);
	check_alloc(data, path);
	if (chdir(path) < 0)
	{
		handle_strerror(data, command->command_args[1], EXIT_FAILURE, false);
	}
	free(path);
}

void	ft_unset(t_data *data, t_token *token)
{
	t_command	*command;

	command = token->command;
	if (!(command->command_args)[1])
			return ;
	ft_hash_remove(data->vars, (command->command_args)[1]);
}

void  ft_export(t_data *data, t_token *token)
{
	char **cmd;

	if (!token->command->command_args[1] && token->command->command_args[2])
		return ;
	cmd = split_export_cmd(token->command->command_args[1]);
	if (ft_isalpha(cmd[0][0]) && !ft_strcmp(cmd[1], "+="))
		append_export(data, cmd);
	else if (ft_isalpha(cmd[0][0]) && !ft_strcmp(cmd[1], "="))
		supress_export(data, cmd);
	else
	{
		ft_printfd(2, "export: `%s': not a valid identifier\n", token->command->command_args[1]);
		ft_hash_update(data->vars, LAST_RETURN_CODE, "1");
	}
	ft_free_2d_char_null_ended(cmd);
}

/*
void  ft_export(t_data *data, t_token *token)
{
	int   i;
	char **var;
	char *content;

	i = 1;
	content = NULL;
	if (!token->command->command_args[1])
	{
		ft_print_env_in_order(data);
		return ;
	}
	var = ft_split(token->command->command_args[1], '=');
	while (var[i])
	{
		content = ft_joinfree(content, var[i++]);
		if (var[i])
			content = ft_joinfree(content, "=");
	}
	if (var[0] && ft_isalpha(var[0][0]) && ft_isalnumstr(var[0]) && content)
	{
		ft_hash_remove(data->vars, var[0]);
		ft_hash_insert(data->vars, ft_strdup(var[0]), ft_strdup(content));
	}
	else if (!var[0] || !ft_isalpha(var[0][0]) || !ft_isalnumstr(var[0]))
	{
		ft_printfd(2, "export: `%s': not a valid identifier\n", token->command->command_args[1]);
		ft_hash_update(data->vars, LAST_RETURN_CODE, "1");
	}
	if (content)
		free(content);
	ft_free_2d_char_null_ended(var);
}*/

void	try_exec_single_builtin(t_data *data, t_token *token, t_command *command)
{
	int	i;

	i = 0;
	while (data->exec->builtins[i])
	{
		if (!ft_strcmp(command->command_args[0], data->exec->builtins[i]))
		{
			data->exec->builtin_ptrs[i](data, token);
			return ;
		}
		i++;
	}
}
