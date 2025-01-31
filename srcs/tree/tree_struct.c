
#include "shell.h"

t_tree	*new_tree_node(void)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->value = NULL;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

void	free_tree(t_tree *tree)
{
	if (tree->right)
		free_tree(tree->right);
	if (tree->left)
		free_tree(tree->left);
	if (tree->value)
		free_token(tree->value);
	free(tree);
}
