/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:27:06 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/28 15:57:42 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

void	add_elem(t_splitter *splitter, char **splitted, int len, size_t *i)
{
	int	e;

	e = ft_count_2dchar_null_ended(splitted);
	splitted[e] = ft_substr(splitter->s, *i, len + 1);
	check_malloc(splitter, splitted, splitted[e]);
	*i += len + 1;
}

void	count_word(t_splitter *splitter, size_t *i, int *count)
{
	size_t	len;
	char	*s;

	s = splitter->s;
	len = 0;
	while (s[*i + len] && is_outside_delims(splitter->delims) \
		&& !get_delimiter(&s[*i + len], splitter->delims, 'a') \
		&& !get_sep_not_space(&s[*i + len], splitter->seps))
		len++;
	if (len > 0)
	{
		*count += 1;
		*i += len;
	}
}

void	add_word_outside_delims(t_splitter *splitter, size_t *i, \
	char **splitted)
{
	size_t	len;
	char	*s;

	s = splitter->s;
	len = 0;
	while (s[*i + len] && is_outside_delims(splitter->delims) \
		&& !get_delimiter(&s[*i + len], splitter->delims, 'a') \
		&& !get_sep_not_space(&s[*i + len], splitter->seps))
		len++;
	if (len > 0)
	{
		add_elem(splitter, splitted, len - 1, i);
	}
}

static void	*fill_splitted(t_splitter *splitter, char **seps, \
	t_delimiter **delims, char **splitted)
{
	int		e;
	size_t	i;
	char	*s;

	i = 0;
	e = 0;
	s = splitter->s;
	while (s[i])
	{
		while (s[i] && get_sep(&s[i], seps))
		{
			add_sep(splitter, get_sep(&s[i], seps), &i, splitted);
		}
		while (s[i] && get_delimiter(&s[i], delims, 'a'))
			go_to_end_of_delim(splitter, splitted, &i);
		add_word_outside_delims(splitter, &i, splitted);
	}
	e = ft_count_2dchar_null_ended(splitted);
	splitted[e] = NULL;
	return (splitted);
}

/*
 * requires that all literal delimiters (quotes) are closed
 */
char	**ft_split_skip(const char *str, char **seps, )
{
	t_splitter	*splitter;
	char		**splitted;
	if (!str)
		return (NULL);
	splitter = init_splitter(str, seps, ignore_delimiters);
	splitted = init_splitskipped(splitter, splitter->s, splitter->seps, \
		splitter->delims);
	check_malloc(splitter, splitted, splitted);
	reset_delim_close_status(splitter->delims);
	fill_splitted(splitter, splitter->seps, splitter->delims, splitted);
	free_splitter(splitter);
	return (splitted);
}
