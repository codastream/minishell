/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:27:06 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_sep(char c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (true);
		++sep;
	}
	return (false);
}

static char	**init_splitted(const char *s, char *charset)
{
	int		count;
	size_t	i;
	char	**splitted;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], charset))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_sep(s[i], charset))
			i++;
	}
	splitted = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!splitted)
		return (NULL);
	return (splitted);
}

static void	*ft_free(char **splitted, int e)
{
	while (e > 0)
	{
		free(splitted[e]);
		e--;
	}
	free(splitted);
	return (NULL);
}

static size_t	move_to_word_end(char const *s, size_t *i, char *charset)
{
	size_t	j;

	while (s[*i] && is_sep(s[*i], charset))
		(*i)++;
	j = 0;
	while (s[*i + j] && !is_sep(s[*i + j], charset))
		(j)++;
	return (j);
}

char	**ft_split_str(char const *s, char *charset)
{
	int		e;
	size_t	i;
	size_t	j;
	char	**splitted;

	splitted = init_splitted(s, charset);
	if (!splitted)
		return (NULL);
	i = 0;
	e = 0;
	while (s[i])
	{
		j = move_to_word_end(s, &i, charset);
		if (j > 0)
		{
			splitted[e] = ft_substr(s, i, j);
			if (!splitted[e])
				ft_free(splitted, e);
			e++;
		}
		i += j;
	}
	splitted[e] = NULL;
	return (splitted);
}
