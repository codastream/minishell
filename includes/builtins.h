/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:27:18 by jmassavi          #+#    #+#             */
/*   Updated: 2025/03/27 15:07:40 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	try_exec_builtin_in_fork(t_data *data, t_token *token, \
			t_command *command);
void	try_exec_builtin(t_data *data, t_token *token, t_command *command);
bool	is_builtin(t_data *data, t_command *command);

void	ft_cd(t_data *data, t_token *token);
void	ft_echo(t_data *data, t_token *token);
void	ft_env(t_data *data, t_token *token);
void	ft_exit(t_data *data, t_token *token);
void	ft_export(t_data *data, t_token *token);
char	*getpwd(t_data *data);
void	ft_pwd(t_data *data, t_token *token);
void	ft_unset(t_data *data, t_token *token);

void	append_export(t_data *data, char **cmd);
void	supress_export(t_data *data, char **cmd);

#endif
