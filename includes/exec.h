#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

void	exec_ins(t_tree *tree);
void	do_pipe(t_command command);
void	safe_dup2(int fdfrom, int fdto);
void	safe_pipe(int	fds[2]);
int		safe_fork(void);

#endif
