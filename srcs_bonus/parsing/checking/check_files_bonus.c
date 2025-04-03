/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:47:36 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:57:17 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	is_elf_executable(t_data *data, char *path)
{
	unsigned char	buffer[4];
	int				fd;
	int				read_code;

	fd = open(path, O_RDONLY);
	handle_and_exit_if_negative(data, fd, "Error opening file");
	read_code = read(fd, buffer, 4);
	close(fd);
	if (read_code != 4)
		return (false);
	if (buffer[0] == 0x7F && buffer[1] == 'E' && buffer[2] == 'L' \
		&& buffer[3] == 'F')
		return (true);
	return (false);
}

bool	is_script(t_data *data, char *path)
{
	char	buffer[2];
	int		fd;
	int		read_code;

	fd = open(path, O_RDONLY);
	handle_and_exit_if_negative(data, fd, "Error opening file");
	read_code = read(fd, buffer, 2);
	close(fd);
	if (read_code != 2)
		return (false);
	if (buffer[0] == '#' && buffer[1] == '!')
		return (true);
	return (false);
}
