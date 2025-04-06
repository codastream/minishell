/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:23:22 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:23:55 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

typedef struct s_keyval
{
	char			*key;
	char			*value;
	struct s_keyval	*next;
}	t_keyval;

typedef struct s_hash
{
	t_keyval	**keyvals;
	int			capacity;
	int			elements_nb;
}	t_hash;

unsigned int		hashcode(t_hash *hash, char *key);
t_keyval			*new_node(char *key, char *value);
void				ft_print_hashstr(t_hash *hash);
void				ft_hash_reset(t_hash *hash);
void				ft_free_hashtable(t_hash *hash);
void				free_keyval(t_keyval *keyval);

t_hash				*ft_hash_init(int size);
int					ft_hash_insert(t_hash *hash, char *key, char *value);
int					ft_hash_update(t_hash *hash, char *key, char *new_value);
char				*ft_hash_get(t_hash *hash, char *key);
int					ft_hash_remove(t_hash *hash, char *key);
void				ft_free_hashtable(t_hash *hash);

#endif
