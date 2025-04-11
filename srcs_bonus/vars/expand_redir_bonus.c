/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:57:55 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 13:33:27 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	expand_var_in_redir(t_data *data, char	**file)
{
	char	*s;
	int		last_expanded_index;
	bool	in_dquote;
	char	*expanded;

	last_expanded_index = 0;
	in_dquote = false;
	s = *file;
	if (!ft_strstr(*file, "$"))
		return ;
	while (s && next_expand(s, '$', &last_expanded_index, &in_dquote))
	{
		expanded = try_replace_vars(data, *file, &last_expanded_index, ARG);
		adjust_quote_status(expanded, &last_expanded_index, &in_dquote);
		free(*file);
		*file = expanded;
		s = expanded;
	}
}

void	lst_iter_redir(t_data *data, t_list *lst, void (*f)(t_data *, char **))
{
	t_list	*current;
	t_redir	*redir;

	current = lst;
	if (!lst || !f)
		return ;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->string && redir->type != T_EOF)
			(*f)(data, &redir->string);
		current = current->next;
	}
}
