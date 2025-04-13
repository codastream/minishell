/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:34:18 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/12 17:19:15 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	compute_sublen(char *s, int *i, int len)
{
	int	sublen;

	while (ft_ischarforenvvar(s[*i + len + 1]))
		len++;
	sublen = len + 1;
	return (sublen);
}

bool	should_expand(t_token *token, char *s, bool *varindquote)
{
	int		i;

	i = 0;
	(void) token;
	return (next_expand(s, '$', &i, varindquote));
}

void	adjust_quote_status(char *expanded, int *last_expanded_index, \
	bool *in_dquote)
{
	if (expanded[*last_expanded_index] == '"')
	{
		toggle_quote_status(in_dquote);
		*last_expanded_index += 1;
	}
}

void	nullify_empty_args(char ***arg, int i)
{
	if (!ft_strcmp((*arg)[i], ""))
	{
		free(arg[0][i]);
		arg[0][i] = NULL;
	}
}
