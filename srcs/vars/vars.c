#include "shell.h"

void	get_keyval(char	*s, char **key, char **value)
{
	char	**splitted;

	splitted = ft_split(s, '=');
	if (!splitted)
		return ;
	if (splitted[0])
		*key = ft_strdup(splitted[0]);
	if (splitted[1])
		*value = ft_strdup(splitted[1]);
	else
		*value = NULL;
	ft_free_2d_char_null_ended(splitted);
}

void	init_vars(t_data *data, char **env)
{
	int		env_var_nb;
	int		i;
	t_hash	*vars;
	char	*key;
	char	*value;

	env_var_nb = ft_count_2dchar_null_ended(env);
	vars = ft_hash_init(env_var_nb + 100);
	check_alloc(data, vars);
	i = 0;
	while (i < env_var_nb)
	{
		get_keyval(env[i], &key, &value);
		if (key && value)
			ft_hash_insert(vars, key, value);
		else if (key)
			ft_hash_insert(vars, key, NULL);
		free(key);
		// free(value);
		i++;
	}
	ft_print_hashstr(vars);
	data->vars = vars;
}
