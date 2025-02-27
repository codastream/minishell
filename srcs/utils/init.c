#include "shell.h"

t_data *init_data(char **env)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->prompt = NULL;
	// data->return_code = EXIT_SUCCESS;
	init_vars(data, env);
	return (data);
}
