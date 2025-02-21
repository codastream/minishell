#include "shell.h"

// TODO check alloc
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

char	**hashtab_to_tab(t_data *data, t_hash *hash)
{
	char		**tab;
	int			elem_nb;
	int			i;
	int			i_tab;
	t_keyval	*current;
	char		*to_join[2];

	elem_nb = hash->elements_nb;
	tab = ft_calloc(elem_nb + 1, sizeof(char *));
	check_alloc(data, tab);
	i = 0;
	i_tab = 0;
	while (i < hash->capacity)
	{
		if (hash->keyvals[i])
		{
			current = hash->keyvals[i];
			while (current)
			{
				if (current->key)
					to_join[0] = current->key;
				else
					to_join[0] = "";
				if (current->value)
					to_join[1] = current->value;
				else
					to_join[1] = "";
				tab[i_tab] = ft_multistrjoin(2, to_join, "=");
				check_alloc(data, tab[i_tab]);
				current = current->next;
				i_tab++;
			}
		}
		i++;
	}
	return (tab);
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
		if (value)
			free (value);
		i++;
	}
	ft_hash_insert(vars, LAST_RETURN_CODE, "0");
	// ft_print_hashstr(vars);
	data->vars = vars;
}
void	update_last_return(t_data *data, int code)
{
	char	*code_s;

	code_s = ft_itoa(code);
	ft_hash_update(data->vars, LAST_RETURN_CODE, code_s);
	free(code_s);
}
