/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmassavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:42:19 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/28 17:42:21 by jmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_token	*midle_part(t_token *list)
{
	int		i;
	t_token *tmp_list;

	i = 0;
	tmp_list = list;
	while (tmp_list)
	{
		i++;
		tmp_list = tmp_list->next;
	}
	tmp_list = list;
	i = (i + 1) / 2 - 1;
	while (i != 0)
	{
		i--;
		tmp_list = tmp_list->next;
	}
	while (tmp_list->type != T_PIPE && tmp_list->next)
		tmp_list = tmp_list->next;
	return (tmp_list);
}

t_token	*left_part(t_token *list)
{
	t_token *tmp_list;
	
	tmp_list = midle_part(list);
	tmp_list = tmp_list->prev;
	tmp_list->next = NULL;
	while (tmp_list->prev)
		tmp_list = tmp_list->prev;
	return (tmp_list);
}

t_token	*right_part(t_token *list)
{
	t_token *tmp_list;
	
	tmp_list = midle_part(list);
	tmp_list = tmp_list->prev;
	tmp_list->prev = NULL;
	return (tmp_list);
}

int	len_list(t_token *list)
{
	int	i;
	
	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_tree	*make_tree(t_token *list)
{
	t_tree	*tree;
	
	tree = new_tree_node();
	if (!tree)
		return (NULL);
	tree->value = midle_part(list);
//	printf("%s\n", tree->value->string);
	if (len_list(list) >= 2)
	{
		tree->left = make_tree(left_part(list));
		tree->right = make_tree(right_part(list));
	}
	return (tree);
}
