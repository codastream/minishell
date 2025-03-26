#include "shell.h"
#include "var.h"

void	get_keyval(t_data *data, char	*s, char **key, char **value)
{
	char	**splitted;

	splitted = ft_split(s, '=');
	check_alloc(data, splitted);
	if (!splitted)
		return ;
	if (splitted[0])
	{
		*key = ft_strdup(splitted[0]);
		check_alloc(data, *key);
	}
	if (splitted[1])
	{
		*value = ft_strdup(splitted[1]);
		check_alloc(data, *value);
	}
	else
		*value = NULL;
	ft_free_2d_char_null_ended(splitted);
}

static void	add_keyval_to_tab(t_data *data, t_keyval *current, \
		char **tab, int *i_tab)
{
	char		*to_join[2];

	if (current->key)
		to_join[0] = current->key;
	else
		to_join[0] = "";
	if (current->value)
		to_join[1] = current->value;
	else
		to_join[1] = "";
	tab[*i_tab] = ft_multistrjoin(2, to_join, "=");
	check_alloc(data, tab[*i_tab]);
	(*i_tab)++;
}

char	**hashtab_to_tab(t_data *data, t_hash *hash)
{
	char		**tab;
	int			elem_nb;
	int			i;
	int			i_tab;
	t_keyval	*current;

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
				add_keyval_to_tab(data, current, tab, &i_tab);
				current = current->next;
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
	// t_hash	*expvars;
	char	*key;
	char	*value;
	char	*pwd;

	env_var_nb = ft_count_2dchar_null_ended(env);
	vars = ft_hash_init(env_var_nb + 100);
	// expvars = ft_hash_init(env_var_nb + 100);
	check_alloc(data, vars);
	i = 0;
	while (i < env_var_nb)
	{
		get_keyval(data, env[i], &key, &value);
		if (key && value)
		{
			ft_hash_insert(vars, key, value);
			// ft_hash_insert(expvars, key, value);
		}
		else if (key)
		{
			ft_hash_insert(vars, key, NULL);
			// ft_hash_insert(expvars, key, NULL);
		}
		free(key);
		if (value)
			free (value);
		i++;
	}
	pwd = getpwd(data);
	if (env_var_nb == 0)
	{
		ft_hash_insert(vars, "PWD", pwd);
		ft_hash_insert(vars, "OLDPWD", NULL);
	}
	free(pwd);
	ft_hash_insert(vars, LAST_RETURN_CODE, "0");
	data->localvars = vars;
	// data->expvars = expvars;
}
