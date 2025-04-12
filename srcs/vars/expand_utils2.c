/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:34:18 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/10 14:08:23 by fpetit           ###   ########.fr       */
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

void	adjust_quote_status(char *expanded, char *s, int *last_expanded_index, \
	bool *in_dquote)
{
	int	i;

	i = 0;
	*in_dquote = false;
//	printf("-> %s\n-> %s\n-> %d\n", expanded, s, *last_expanded_index);
	while (s[i])
	{
		if (s[i] == '$')
			return ;
		if (s[i] == '"')
			skip_quote(s, &i, '"');
		if (s[i] == '\'')
			skip_quote(s, &i, '\'');
		i++;
	}
	*in_dquote = true;
	(void)expanded;
	(void)last_expanded_index;

}
