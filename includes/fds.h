#ifndef FDS_H
# define FDS_H

# include "shell.h"

void	fd_push_back(t_fds **head, int fd);
void	pop_fd(t_fds **fds, int fd);
void	pop_all_fd(t_fds **head);

#endif
