/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:21:54 by fpetit            #+#    #+#             */
/*   Updated: 2024/11/27 13:13:01 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_char(char *s, char c)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*init_buffer(void)
{
	size_t	i;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE + 1)
		buffer[i++] = '\0';
	return (buffer);
}

char	*read_line(int fd, char *extra)
{
	ssize_t	rd;
	char	*buffer;

	buffer = init_buffer();
	if (!buffer)
		return (NULL);
	rd = 1;
	while (rd != 0 && (!has_char(extra, '\n')))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1 || (rd == 0 && (!extra || extra[0] == '\0')))
		{
			free(buffer);
			return (NULL);
		}
		if (rd != 0)
		{
			buffer[rd] = '\0';
			extra = ft_strjoin_free_first(extra, buffer);
		}
	}
	free(buffer);
	return (extra);
}

/*
 * returns:
 * a line with final \n
 * NULL when we reached the end of file
 * error cases:
 * returns NULL if fd represents an error at opening (-1)
 * returns NULL if BUFFERSIZE doesn't allow to read
 * returns NULL in case of read error
 */
char	*get_next_line(int fd)
{
	static char	*extra[MAX_FD];
	char		*line;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, extra[fd]);
	if (!line)
	{
		free(extra[fd]);
		extra[fd] = NULL;
		return (NULL);
	}
	extra[fd] = get_extra(line);
	line = trim_line(line);
	return (line);
}
