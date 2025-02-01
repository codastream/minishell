/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:56:16 by jmassavi          #+#    #+#             */
/*   Updated: 2025/02/01 20:22:21 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "parsing.h"

t_tree	*new_tree_node(void);
void	free_tree(t_tree *tree);
void	print_tree(t_tree *root);

t_tree	*make_tree(t_token *list);
int		iter_tree_count(t_tree *tree, int *count, void (*f)(t_tree *, int *));
void	count_if_command(t_tree *tree, int *nb);

#endif
