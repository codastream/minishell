#include "shell.h"

void	count_if_command(t_tree *tree, int *nb)
{
	if (tree && tree->value && tree->value->type == T_COMMAND)
		*nb += 1;
}

int	iter_tree_count(t_tree *tree, int *count, void (*f)(t_tree *, int *))
{
	if (!tree)
		return (0);
	iter_tree_count(tree->left, count, f);
	f(tree, count);
	iter_tree_count(tree->right, count, f);
	return (*count);
}
/*
 * to be used with check redirection files
 */
int	iter_tree_token(t_data *data, t_tree *tree, int (*f)(t_data *data, t_token *token))
{
	if (!tree)
		return (EXIT_IGNORE);
	iter_tree_token(data, tree->left, f);
	// if (code != EXIT_SUCCESS)
	// 	return (code);
	f(data, tree->value);
	// if (code != EXIT_SUCCESS)
	// 	return (code);
	iter_tree_token(data, tree->right, f);
	// if (code != EXIT_SUCCESS)
	// 	return (code);
	return (EXIT_SUCCESS);
}
