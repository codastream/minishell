/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:35:10 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:35:41 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_keyval(t_keyval *keyval)
{
	free(keyval->key);
	keyval->key = NULL;
	free(keyval->value);
	keyval->value = NULL;
	free(keyval);
	keyval = NULL;
}

/*
 * returns 1 if no value for this key
 * returns 0 if has been deleted
 */
int	ft_hash_remove(t_hash *hash, char *key)
{
	unsigned int	index;
	t_keyval		*current;
	t_keyval		*previous;

	index = hashcode(hash, key);
	previous = NULL;
	current = hash->keyvals[index];
	if (!current)
		return (EXIT_FAILURE);
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (!previous)
				hash->keyvals[index] = current->next;
			else
				previous->next = current->next;
			free_keyval(current);
			hash->elements_nb--;
			return (EXIT_SUCCESS);
		}
		previous = current;
		current = current->next;
	}
	return (EXIT_FAILURE);
}
