/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:24:27 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:34:23 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * returns a hash for the key
 * using a prime number (31) helps reduce collision risks
 */
unsigned int	hashcode(t_hash *hash, char *key)
{
	unsigned long int	value;
	unsigned int		i;
	unsigned int		key_len;

	value = 0;
	i = 0;
	key_len = ft_strlen(key);
	while (i < key_len)
	{
		value = value * 31 + key[i];
		i++;
	}
	return (value % hash->capacity);
}

t_keyval	*new_node(char *key, char *value)
{
	t_keyval	*keyval;

	keyval = ft_calloc(1, sizeof(t_keyval));
	if (!keyval)
		return (NULL);
	keyval->key = ft_strdup(key);
	if (!keyval->key)
		return (NULL);
	if (!value)
	{
		keyval->value = malloc(1);
		keyval->value[0] = '\0';
	}
	else
	{
		keyval->value = ft_strdup(value);
		if (!keyval->value)
			return (NULL);
	}
	keyval->next = NULL;
	return (keyval);
}

void	ft_hash_reset(t_hash *hash)
{
	int	i;

	i = 0;
	while (i < hash->capacity)
	{
		hash->keyvals[i] = NULL;
		i++;
	}
}
/*
 * will consider values have been allocated
 */

void	ft_free_hashtable(t_hash *hash)
{
	int			i;
	t_keyval	*current;
	t_keyval	*tmp;

	i = 0;
	while (i < hash->capacity)
	{
		if (hash->keyvals[i])
		{
			current = hash->keyvals[i];
			while (current)
			{
				tmp = current;
				current = current->next;
				free_keyval(tmp);
			}
		}
		i++;
	}
	free(hash->keyvals);
	free(hash);
}

void	ft_print_hashstr(t_hash *hash)
{
	int			i;
	t_keyval	**keyvals;
	t_keyval	*current;

	keyvals = hash->keyvals;
	i = 0;
	while (i < hash->capacity)
	{
		if (keyvals[i])
		{
			ft_printf("#%d : ", i);
			current = keyvals[i];
			while (current)
			{
				ft_printf("\t%s -> %s\n", current->key, \
					(char *) current->value);
				current = current->next;
			}
		}
		i++;
	}
}
