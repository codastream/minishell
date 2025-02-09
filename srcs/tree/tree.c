#include "../../includes/shell.h"

t_token	*get_central_token(t_token **tokens)
{
	int		size;
	int		i;
	t_token *current;

	size = get_tokens_nb(tokens);
	i = 0;
	current = *tokens;
	if (size == 0)
		return (NULL);
	if (size == 1)
		return (current);
	while (i < (size / 2))
	{
		current = current->next;
		i++;
	}
	while (current->next && current->type != T_PIPE)
		current = current->next;
	return (current);
}

void split(t_token **tokens, t_token **left, t_token **right)
{
	t_token *current;

	current = get_central_token(tokens);
	current = current->prev;
	*right = current->next->next;
	current->next = NULL;
	while (current->prev)
		current = current->prev;
	*left = current;
}

void	count_if_command(t_tree *tree, int *nb)
{
	if (tree && tree->value && tree->value->type == T_COMMAND)
		*nb += 1;
}

int iter_tree_count(t_tree *tree, int *count, void (*f)(t_tree *, int *))
{
	if (!tree)
		return (0);
	iter_tree_count(tree->left, count, f);
	f(tree, count);
	iter_tree_count(tree->right, count, f);
	return (*count);
}

t_tree	*make_tree(t_token *tokens)
{
	t_tree	*tree;
	t_token	*left;
	t_token *right;

	tree = new_tree_node();
	if (!tree)
		return (NULL);
	tree->value = get_central_token(&tokens);
	if (get_tokens_nb(&tokens) >= 2)
	{
		split(&tokens, &left, &right);
		tree->left = make_tree(left);
		tree->right = make_tree(right);
	}
	return (tree);
}

void	add_node_before(t_tree **root, t_tree *node)
{
	if (!*root)
	{
		*root = node;
		return ;
	}
	node->left = *root;
	*root = node;
}


int	ft_tree_get_max_depth(t_tree *tree)
{
	int		left_depth;
	int		right_depth;

	if (!tree)
		return (0);
	left_depth = ft_tree_get_max_depth(tree->left);
	right_depth = ft_tree_get_max_depth(tree->right);
	if (left_depth > right_depth)
		return (left_depth + 1);
	else
		return (right_depth + 1);
}

void	print_pretty_tree(t_tree *tree, int level, char *prefix)
{
	int	i;

	if (tree)
	{
		if (tree->right)
			print_pretty_tree(tree->right, level + 1, "┌--");
		i = 0;
		while (i < level)
		{
			printf("\t");
			i++;
		}
		printf("%s%s%s%s\n", prefix, P_BLUE, tree->value->string, P_NOC);
		if (tree->left)
			print_pretty_tree(tree->left, level + 1, "└--");
	}
}
