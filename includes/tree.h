/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:56:16 by jmassavi          #+#    #+#             */
/*   Updated: 2025/02/02 17:01:20 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "parsing.h"

t_tree	*new_tree_node(void);

t_tree	*make_tree(t_data *data, t_token *list);
int		iter_tree_count(t_tree *tree, int *count, void (*f)(t_tree *, int *));
void	count_if_command(t_tree *tree, int *nb);
int		ft_tree_get_max_depth(t_tree *tree);
void	print_pretty_tree(t_data *data, t_tree *tree, int level, char *prefix, bool show_pipe_fds);
void	iter_tree_modify(t_tree *tree, void (*f)(t_tree *));
void	init_fds(t_tree *tree);

#endif
