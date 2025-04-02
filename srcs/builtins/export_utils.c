/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:05 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/31 21:15:54 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	len_hash_table(t_hash *hash)
{
	int	i;
	int	len;
	t_keyval	**keyvals;
	t_keyval	*current;

	i = 0;
	len = 0;
	keyvals = hash->keyvals;
	while (i < hash->capacity)
	{
		if (keyvals[i])
		{
			current = keyvals[i];
			while (current)
			{
				len++;
				current = current->next;
			}
		}
		i++;
	}
	return (len);
}

char **hash_table_to_tab(t_hash *hash)
{
	int	  i;
	int	  j;
	char  **tab;
	t_keyval	**keyvals;
	t_keyval	*current;

	i = 0;
	j = 0;
	keyvals = hash->keyvals;
	tab = ft_calloc(len_hash_table(hash) + 1, sizeof(char *));
	while (i < hash->capacity)
	{
		if (keyvals[i])
		{
			current = keyvals[i];
			while (current)
			{
				tab[j++] = ft_strdup(current->key);
				current = current->next;
			}
		}
		i++;
	}
	return (tab);
}

bool	is_valid_identifier(char *arg)
{
	if (!arg)
		return (false);
	if (arg[0] == '=')
		return (false);
	return (true);
}

char	**generate_export_split(char **result, char *cmd, int i, int j)
{
	int	code;

	code = ft_strndup(&result[1], cmd, j, i);
	if (!code)
		ft_free_2d_char_null_ended(result);
	code = ft_strndup(&result[2], cmd, i, ft_strlen(cmd));
	if (!code)
		ft_free_2d_char_null_ended(result);
	return (result);
}
