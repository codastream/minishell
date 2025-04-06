/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:27:06 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**init_splitted(const char *s, char sep)
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
		while (s[i] && s[i] == sep)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != sep)
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

static size_t	move_to_word_end(char const *s, size_t *i, char c)
{
	size_t	j;

	while (s[*i] && s[*i] == c)
		(*i)++;
	j = 0;
	while (s[*i + j] && s[*i + j] != c)
		(j)++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		e;
	size_t	i;
	size_t	j;
	char	**splitted;

	splitted = init_splitted(s, c);
	if (!splitted)
		return (NULL);
	i = 0;
	e = 0;
	while (s[i])
	{
		j = move_to_word_end(s, &i, c);
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
