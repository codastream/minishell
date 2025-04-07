/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:03:32 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:57:33 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

void	reset_delim_close_status(t_delimiter **delims)
{
	int		i;

	i = 0;
	while (delims[i])
	{
		delims[i]->is_closed = true;
		i++;
	}
}

t_splitter	*init_splitter(const char *str, char **seps, \
		t_delimiter **ignore_delimiters)
{
	t_splitter	*splitter;

	splitter = ft_calloc(1, sizeof(t_splitter));
	if (!splitter)
		return (NULL);
	splitter->s = (char *) str;
	splitter->index = 0;
	splitter->count = 0;
	splitter->delims = NULL;
	splitter->delims = ignore_delimiters;
	splitter->seps = seps;
	check_malloc(splitter, NULL, splitter->delims);
	return (splitter);
}

int	count_elems(t_splitter *splitter, char *s, char **seps, \
		t_delimiter **delims)
{
	size_t		i;
	size_t		word_len;
	int			count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && get_sep(&s[i], seps))
			count_sep(get_sep(&s[i], seps), &i, &count);
		word_len = i;
		while (s[word_len] && !get_sep(&s[word_len], seps))
		{
			while (get_del(&s[word_len], delims, 'a'))
				go_to_end_of_delim_count(splitter, delims, &word_len, &count);
			while (s[word_len] && !get_sep(&s[word_len], seps) && \
				!get_del(&s[word_len], delims, 'a'))
				word_len++;
		}
		if (word_len > i)
			count++;
		i = word_len;
	}
	return (count);
}

char	**init_splitskipped(t_splitter *splitter, char *s, char **seps, \
	t_delimiter **delims)
{
	int			count;
	char		**splitted;

	if (!s)
		return (NULL);
	count = count_elems(splitter, s, seps, delims);
	splitted = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!splitted)
		return (NULL);
	return (splitted);
}
