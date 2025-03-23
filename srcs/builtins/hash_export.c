#include "shell.h"

void	append_export(t_data *data, char **cmd)
{
	char	*result;

	result = ft_hash_get(data->localvars, cmd[0]);
	if (!result)
	{
		ft_hash_insert(data->expvars, cmd[0], cmd[2]);
		ft_hash_insert(data->localvars, cmd[0], cmd[2]);
	}
	else
	{
		result = ft_strjoin(result, cmd[2]);
		ft_hash_update(data->localvars, cmd[0], result);
		ft_hash_update(data->expvars, cmd[0], result);
		free(result);
	}
}

void	supress_export(t_data *data, char **cmd)
{
	ft_hash_remove(data->localvars, cmd[0]);
	ft_hash_insert(data->localvars, cmd[0], cmd[2]);
	ft_hash_remove(data->expvars, cmd[0]);
	ft_hash_insert(data->expvars, cmd[0], cmd[2]);
}
