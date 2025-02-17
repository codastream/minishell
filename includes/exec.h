#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

int		exec_line(t_data *data, t_tree *tree);
void	exec_tree_node(t_data *data, t_tree *tree);
void	safe_dup2(t_data *data, int fdfrom, int fdto);
void	safe_pipe(t_data *data, int	fds[2]);
int		safe_fork(t_data *data);

void  put_fd(t_data *data, t_tree **tree, int in, int out);
void  init_heredoc(t_data *data, t_tree **tree);

#endif
