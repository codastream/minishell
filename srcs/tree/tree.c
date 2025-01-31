/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:42:19 by jmassavi          #+#    #+#             */
/*   Updated: 2025/01/31 20:15:11 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*midle_part(t_token *tokens)
{
	int		size;
	int		i;
	t_token *current;

	size = get_tokens_nb(tokens);
	i = 0;
	current = tokens;
	while (i < (size / 2))
	{
		current = current->next;
		i++;
	}
	while (current->next && current->type != T_PIPE)
		current = current->next;
	// i = (size + 1) / 2 - 1; // size 3 -> i 1
	// while (i != 0)
	// {
	// 	i--;
	// 	current = current->next;
	// }
	// while (current->type != T_PIPE && current->next)
	// 	current = current->next;
	return (current);
}



void split(t_token *tokens, t_token **left, t_token **right)
{
	t_token *current;

	current = midle_part(tokens);
	current = current->prev;
	*right = current->next->next;
	current->next = NULL;
	while (current->prev)
		current = current->prev;
	*left = current;
}

// t_token	*right_part(t_token *tokens)
// {
// 	t_token *current;

// 	current = midle_part(tokens);
// 	current = current->prev;
// 	current->prev = NULL;
// 	return (current);
// }

t_tree	*make_tree(t_token *tokens)
{
	t_tree	*tree;
	t_token	*left;
	t_token *right;

	tree = new_tree_node();
	if (!tree)
		return (NULL);
	tree->value = midle_part(tokens);
//	printf("%s\n", tree->value->string);
	if (get_tokens_nb(tokens) >= 2)
	{
		split(tokens, &left, &right);
		tree->left = make_tree(left);
		tree->right = make_tree(right);
	}
	return (tree);
}
