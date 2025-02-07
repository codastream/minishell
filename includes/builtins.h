/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmassavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:27:18 by jmassavi          #+#    #+#             */
/*   Updated: 2025/02/07 09:29:10 by jmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	try_exec_buildins(t_data *data, t_command *command);
void	try_exec_first_buildins(t_data *data, t_command *command);

bool	is_buildins(t_command *command);

char	*ft_joinfree(char *str1, char *str2);
char	*getpwd(void);

#endif
