/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:05:35 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:53:26 by fpetit           ###   ########.fr       */
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
	*count += 0;
	*i += len + 1;
}

void	go_to_end_of_delim_count(t_splitter *splitter, t_delimiter **delims, \
	size_t *i, int *count)
{
	t_delimiter	*opening_delim;
	t_delimiter	*closing_delim;
	int			len_delim_token;
	char		*s;

	(void) count;
	s = splitter->s;
	opening_delim = get_del(&s[*i], delims, 'o');
	closing_delim = get_del(&s[*i], delims, 'c');
	if (opening_delim)
	{
		if (is_outside_delims(delims))
		{
			len_delim_token = count_len_till_closing_delim(&s[*i], \
				opening_delim);
			if (len_delim_token > 0)
				*i += len_delim_token + 1;
		}
		else
			*i += ft_strlen(opening_delim->opening);
	}
	else if (closing_delim)
		*i += ft_strlen(closing_delim->closing);
}

void	go_to_end_of_delim(t_splitter *splitter, char **splitted, size_t *i)
{
	t_delimiter	*opening_delim;
	t_delimiter	*closing_delim;
	int			len_delim_token;

	(void) splitted;
	opening_delim = get_del(&splitter->s[*i], splitter->delims, 'o');
	closing_delim = get_del(&splitter->s[*i], splitter->delims, 'c');
	if (opening_delim)
	{
		if (is_outside_delims(splitter->delims))
		{
			len_delim_token = count_len_till_closing_delim(&splitter->s[*i], \
				opening_delim);
			if (len_delim_token > 0)
				*i += len_delim_token + 1;
		}
		else
			*i += ft_strlen(opening_delim->opening);
	}
	else if (closing_delim)
	{
		*i += ft_strlen(closing_delim->closing);
	}
}
