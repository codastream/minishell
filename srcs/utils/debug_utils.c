/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:10:57 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 19:13:32 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_tree(t_tree *root)
{
	t_tree	*current;

	if (!root)
		return ;
	current = root;
	print_tree(current->left);
	if (current->left)
		printf("->");
	if (current->value)
		printf("%s%s%s (%s)", P_BLUE, current->value->string, P_NOC, \
				get_token_type(current->value->type));
	if (current->left)
		printf("->");
	print_tree(current->right);
}

void	print_pretty_tree(t_data *data, t_tree *tree, int level, \
		char *prefix)
{
	int	i;

	if (tree)
	{
		if (tree->right)
			print_pretty_tree(data, tree->right, level + 1, "┌--");
		i = 0;
		while (i < level)
		{
			printf("\t");
			i++;
		}
		printf("%s%s%s%s (in:%d out:%d)", prefix, P_BLUE, tree->value->string, \
				P_NOC, tree->value->in, tree->value->out);
		if (tree->value->type == T_PIPE && tree->value->pipe_read)
			printf("[%sfds 0:%d 1:%d %s]\n", P_PINK, tree->value->pipe_read, \
				tree->value->pipe_write, P_NOC);
		else
			printf("\n");
		if (tree->left)
			print_pretty_tree(data, tree->left, level + 1, "└--");
	}
}

char	*get_token_type_redir(t_tokentype type)
{
	if (type == T_REDIR_HEREDOC)
		return ("redirect heredoc");
	else if (type == T_REDIR_IN)
		return ("redirect infile");
	else if (type == T_REDIR_TRUNCATE)
		return ("redirect outfile");
	else if (type == T_REDIR_APPEND)
		return ("redirect append");
	else if (type == T_EOF)
		return ("eof");
	else if (type == T_INFILE)
		return ("infile");
	else if (type == T_OUTFILE_APPEND)
		return ("outfile >>");
	else if (type == T_OUTFILE_TRUNCATE)
		return ("outfile >");
	else
		return ("no");
}

char	*get_token_type(t_tokentype type)
{
	char	*redir;

	redir = get_token_type_redir(type);
	if (ft_strcmp("no", redir))
		return (redir);
	if (type == T_WORD)
		return ("word");
	else if (type == T_PIPE)
		return ("pipe");
	else if (type == T_LITERAL_SINGLE)
		return ("single quote literal");
	else if (type == T_LITERAL_DOUBLE)
		return ("double quote literal");
	else if (type == T_COMMAND)
		return ("command");
	else
		return ("unknown");
}

void	print_datafds(t_data *data)
{
	t_fds	*fd;

	fd = data->fds;
	while (fd)
	{
		printf("fd %d\n", fd->fd);
		fd = fd->next;
	}
}
