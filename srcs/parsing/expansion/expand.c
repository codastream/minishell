#include "shell.h"

void	expand_var(t_data *data, char **var, char **envp)
{
	int		i;
	int		len;
	char	*key;
	char	*result;

	if (!var || !*var)
		return ;
	key = *var;
	key++;
	result = ft_hash_get(data->vars, key);
	return (result);
}
