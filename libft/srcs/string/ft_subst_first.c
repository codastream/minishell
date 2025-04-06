/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subst_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:50:50 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/03 23:46:56 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy(char *dest, char *src, int *i, int *j)
{
	dest[*j] = src[*i];
	(*j)++;
	(*i)++;
}

static void	add_string_final(char *s, int i)
{
	if (s[i] != '\0')
		s[i] = '\0';
}

static void	replace_str(t_replace *rep, char *replaced)
{
	int		i;
	int		j;
	size_t	len_to_r;

	len_to_r = ft_strlen(rep->to_rep);
	i = 0;
	j = 0;
	while (rep->s[i])
	{
		while (rep->s[i] && i < rep->after_i)
			copy(replaced, rep->s, &i, &j);
		while (rep->s[i] && !ft_strstr(&rep->s[i], rep->to_rep))
			copy(replaced, rep->s, &i, &j);
		replaced[j] = '\0';
		if (rep->s[i] && ft_strstr(&rep->s[i], rep->to_rep))
		{
			ft_strcat(replaced, rep->replacement);
			i += len_to_r;
			j += ft_strlen(rep->replacement);
		}
		while (rep->s[i])
			copy(replaced, rep->s, &i, &j);
	}
	add_string_final(replaced, j);
}

char	*ft_subst_first_after_i(char *s, char *to_replace, char *replacement, \
		int i)
{
	char		*replaced;
	t_replace	*replace;

	if (!s)
		return (NULL);
	if (!to_replace)
		return (s);
	replace = ft_calloc(1, sizeof(t_replace));
	if (!replace)
		return (NULL);
	replace->after_i = i;
	replace->s = s;
	replace->replacement = replacement;
	replace->to_rep = to_replace;
	replaced = ft_calloc(ft_strlen(s) - (ft_strlen(to_replace) * 1) + \
		(ft_strlen(replacement) * 1) + 1, sizeof(char));
	if (!replaced)
		return (NULL);
	replace_str(replace, replaced);
	free(replace);
	return (replaced);
}
