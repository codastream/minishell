/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:27:18 by jmassavi          #+#    #+#             */
/*   Updated: 2025/04/08 23:00:39 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

void	try_exec_builtin_in_fork(t_data *data, t_token *token, \
			t_command *command);
void	try_exec_builtin(t_data *data, t_token *token, t_command *command);
bool	is_builtin(t_data *data, t_command *command);

void	ft_cd(t_data *data, t_token *token);
void	print_path_if_needed(t_command *command, t_token *token, \
			char *path);
char	*get_old_path(t_data *data);
char	*update_oldpwd(t_data *data);
void	ft_echo(t_data *data, t_token *token);
void	ft_env(t_data *data, t_token *token);
void	ft_exit(t_data *data, t_token *token);
char	**generate_export_split(char **result, char *cmd, int i, int j);
void	ft_export(t_data *data, t_token *token);
bool	is_valid_identifier(char *arg);
char	*getpwd(t_data *data);
void	ft_pwd(t_data *data, t_token *token);
void	ft_unset(t_data *data, t_token *token);

void	append_export(t_data *data, char **cmd);
void	supress_export(t_data *data, char **cmd);

#endif
