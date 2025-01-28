/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmassavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:56:16 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/28 18:56:19 by jmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "shell.h"

typedef	struct s_tree
{
	t_token			*value;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

t_tree	*new_tree_node(void);
void	free_tree(t_tree *tree);

t_tree	*make_tree(t_token *list);

#endif
