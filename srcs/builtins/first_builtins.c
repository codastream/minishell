#include "shell.h"

void	ft_exit(t_data *data, t_token *token)
{
	int	return_code = 0;

	if (token->command->command_args[1])
		return_code = ft_atoi(token->command->command_args[1]) % 255;
//	else
//		return_code = data->return_code;
	if (token->out == 1)
		ft_printfd(token->out, "exit\n");
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
		ft_printfd(token->out, "%s", (command->command_args)[i++]);
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
	if (!(command->command_args)[1])
	{
		chdir(ft_hash_get(data->vars, "HOME"));
		return ;
	}
	path = ft_joinfree(getpwd(data), "/");
	check_alloc(data, path);
	path = ft_joinfree(path, (command->command_args)[1]);
	check_alloc(data, path);
	if (chdir(path) < 0)
		ft_printfd(2, "error\n");
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
  int   i;
  char **var;
  char *content;

  i = 1;
  content = NULL;
  if (!token->command->command_args[1])
   return ;
  var = ft_split(token->command->command_args[1], '=');
  while (var[i])
  {
    content = ft_joinfree(content, var[i++]);
    if (var[i])
      content = ft_joinfree(content, "=");
  }
  ft_hash_remove(data->vars, var[0]);
  ft_hash_insert(data->vars, ft_strdup(var[0]), ft_strdup(content));
  if (content)
    free(content);
  ft_free_2d_char_null_ended(var);
}

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
