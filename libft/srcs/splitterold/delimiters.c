/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:05:35 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/22 18:46:59 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

int	count_len_till_closing_delim(char *s, t_delimiter *delim)
{
	int	len;

	len = 1;
	while (s[len] && ft_strncmp(&s[len], delim->closing, \
		ft_strlen(delim->closing)))
		len++;
	if (!ft_strncmp(&s[len], delim->closing, ft_strlen(delim->closing)))
		return (len);
	else
		return (-1);
}

void	count_elem(size_t *i, int len, int *count)
{
	*count += 1;
	*i += len + 1;
}

void	go_to_end_of_delim_count(t_splitter *splitter, t_delimiter **delims, size_t *i, \
	int *count)
{
	t_delimiter	*opening_delim;
	t_delimiter	*closing_delim;
	int			len_delim_token;
	char		*s;

	s = splitter->s;
	opening_delim = get_delimiter(&s[*i], delims, 'o');
	closing_delim = get_delimiter(&s[*i], delims, 'c');
	if (opening_delim)
	{
		if (is_outside_delims(delims))
		{
			opening_delim->is_closed = false;
			len_delim_token = count_len_till_closing_delim(&s[*i], \
				opening_delim);
			if (len_delim_token > 0)
				count_elem(i, len_delim_token, count);
			opening_delim->is_closed = true;
		}
		else
			count_elem(i, ft_strlen(opening_delim->opening), count);
	}
	else if (closing_delim)
		count_elem(i, ft_strlen(closing_delim->closing), count);
}

void	go_to_end_of_delim(t_splitter *splitter, char **splitted, size_t *i)
{
	t_delimiter	*opening_delim;
	t_delimiter	*closing_delim;
	int			len_delim_token;

	opening_delim = get_delimiter(&splitter->s[*i], splitter->delims, 'o');
	closing_delim = get_delimiter(&splitter->s[*i], splitter->delims, 'c');
	if (opening_delim)
	{
		if (is_outside_delims(splitter->delims))
		{
			opening_delim->is_closed = false;
			len_delim_token = count_len_till_closing_delim(&splitter->s[*i], \
				opening_delim);
			if (len_delim_token > 0)
				add_elem(splitter, splitted, len_delim_token, i);
			opening_delim->is_closed = true;
		}
		else
			add_elem(splitter, splitted, ft_strlen(opening_delim->opening), i);
	}
	else if (closing_delim)
	{
		add_elem(splitter, splitted, ft_strlen(closing_delim->closing), i);
	}
}
