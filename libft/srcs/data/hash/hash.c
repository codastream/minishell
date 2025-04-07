/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:24:27 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:36:50 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_prime_above(int n)
{
	if (ft_is_even(n))
		n++;
	while (!ft_is_prime(n))
		n += 2;
	return (n);
}

t_hash	*ft_hash_init(int size)
{
	int			capacity;
	t_keyval	**keyvals;
	t_hash		*hash;

	hash = ft_calloc(1, sizeof(t_hash));
	if (!hash)
		return (NULL);
	capacity = get_prime_above(size);
	hash->capacity = capacity;
	keyvals = ft_calloc(capacity, sizeof (t_keyval *));
	if (!keyvals)
		return (NULL);
	hash->keyvals = keyvals;
	hash->elements_nb = 0;
	ft_hash_reset(hash);
	return (hash);
}
/*
 * use only if value has previously been set
 */

int	ft_hash_update(t_hash *hash, char *key, char *new_value)
{
	unsigned int	index;
	t_keyval		*current;

	index = hashcode(hash, key);
	if (!hash->keyvals[index])
		return (EXIT_FAILURE);
	current = hash->keyvals[index];
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			free(current->value);
			current->value = ft_strdup(new_value);
			return (EXIT_SUCCESS);
		}
		current = current->next;
	}
	if (!current)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
 * returns 0 if the value has been inserted for this key
 */
int	ft_hash_insert(t_hash *hash, char *key, char *value)
{
	unsigned int	index;
	t_keyval		*new_keyval;
	t_keyval		*current;

	if (!key)
		return (EXIT_FAILURE);
	new_keyval = new_node(key, value);
	index = hashcode(hash, key);
	if (!hash->keyvals[index])
		hash->keyvals[index] = new_keyval;
	else
	{
		current = hash->keyvals[index];
		while (current->next)
			current = current->next;
		current->next = new_keyval;
	}
	hash->elements_nb++;
	return (EXIT_SUCCESS);
}

/*
 * returns value of the node at matching hashed index
 * and with matching key
 * returns NULL if not found
 */
char	*ft_hash_get(t_hash *hash, char *key)
{
	unsigned int	index;
	t_keyval		*current;

	index = hashcode(hash, key);
	current = hash->keyvals[index];
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
