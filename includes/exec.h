#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

void	exec_line(t_data *data, t_tree *tree);
void	exec_tree_node(t_data *data, t_tree *tree);
void	safe_dup2(t_data *data, int fdfrom, int fdto);
void	safe_pipe(t_data *data, int	fds[2]);
int		safe_fork(t_data *data);

void	put_fd(t_data *data, t_tree **tree, int in, int out);
void	put_fd_token(t_data *data, t_token *token, int in, int out);
int		heredoc(t_data *data, t_tree **tree);
void	close_all(t_tree *tree);
int		check_executable(t_data *data, t_token *token);

int		check_redirection_files(t_data *data, t_token **tokens, t_token *token);

// int		redir_data(t_data *data, t_tree **tree_p);

#endif
