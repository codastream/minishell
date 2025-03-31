/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:01:09 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/30 19:28:19 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

// exec
void	exec_line(t_data *data, t_tree *tree);
void	exec_tree_node(t_data *data, t_tree *tree);

// exec utils
void	safe_dup2(t_data *data, int fdfrom, int fdto);
void	safe_pipe(t_data *data, int fds[2]);
int		safe_fork(t_data *data);
void	put_fd(t_data *data, t_tree **tree, int in, int out);
void	put_fd_token(t_data *data, t_token *token, int in, int out);

// fds utils
void	assign_fd(t_data *data, t_tree *pipenode, t_tree *tree, bool is_left);

// heredoc
int		init_heredoc(t_data *data, t_list *currentredir, t_redir *redir);

// heredoc utils
void	put_fd_heredoc(t_data *data, t_tree **tree, int in, int out);
char	*get_last_eofmarker(t_command *command);

// void	close_all(t_tree *tree);
int		check_executable(t_data *data, t_token *token);

// exec redir
int		check_redirection_files(t_data *data, t_token *token);

// redir utils
bool	has_type_of_redir(t_command *command, t_tokentype type);
bool	has_redirin(t_tree *tree);
bool	has_redirout(t_tree *tree);
bool	is_input_redir(t_redir *redir);
bool	is_output_redir(t_redir *redir);

// exec utils 2
int		wait_all(t_data *data, t_exec *exec);
void	check_exec_builtin(t_data *data, t_tree *tree);

#endif
