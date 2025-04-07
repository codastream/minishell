/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:05:35 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:53:26 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

t_delimiter	*get_del(char *s, t_delimiter **delims, char delim_type)
{
	int		i;
	size_t	len_open;
	size_t	len_close;

	i = 0;
	while (delims[i])
	{
		len_open = ft_strlen(delims[i]->opening);
		len_close = ft_strlen(delims[i]->closing);
		if (delim_type == 'o' && !ft_strncmp(s, delims[i]->opening, len_open))
			return (delims[i]);
		if (delim_type == 'c' && !ft_strncmp(s, delims[i]->closing, len_close))
			return (delims[i]);
		if (delim_type == 'a' && (!ft_strncmp(s, delims[i]->opening, len_open) \
			|| !ft_strncmp(s, delims[i]->closing, len_close)))
			return (delims[i]);
		i++;
	}
	return (NULL);
}

bool	is_outside_delims(t_delimiter **delims)
{
	int		i;

	i = 0;
	while (delims[i])
	{
		if (delims[i]->is_closed == false)
			return (false);
		i++;
	}
	return (true);
}

bool	can_split_delim(t_delimiter **delims, t_delimiter *delim)
{
	int		i;

	i = 0;
	while (delims[i])
	{
		if (delims[i] != delim && !delims[i]->is_closed)
			return (false);
		i++;
	}
	return (false);
}
