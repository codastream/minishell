#include "../../includes/shell.h"

static t_tree	*new_tree_node(void)
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

static t_token	*get_central_token(t_token **tokens)
{
	int		size;
	int		i;
	t_token	*current;

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

static void	split(t_token **tokens, t_token **left, t_token **right)
{
	t_token	*current;

	current = get_central_token(tokens);
	current = current->prev;
	if (current->next && current->next->next)
	{
		*right = current->next;
		(*right)->prev = NULL;
	}
	current->next = NULL;
	while (current->prev)
		current = current->prev;
	*left = current;
}

t_tree	*make_tree(t_data *data, t_token *tokens)
{
	t_tree	*tree;
	t_token	*left;
	t_token	*right;

	tree = new_tree_node();
	check_alloc(data, tree);
	tree->value = get_central_token(&tokens);
	if (get_tokens_nb(&tokens) > 2)
	{
		split(&tokens, &left, &right);
		tree->left = make_tree(data, left);
		tree->right = make_tree(data, right);
	}
	return (tree);
}
