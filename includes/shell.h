#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>				// malloc, free, getenv
# include <fcntl.h>					// open, close
# include <stdio.h>					// printf
# include <unistd.h>				// fork, execve, access, dup, dup2, pipe, read, write, unlink, exit, getcwd, chdir
# include <sys/wait.h>				// waitpid
# include <sys/types.h>
# include <sys/stat.h>				// stat, lstat, fstat
# include <dirent.h>				// opendir, readdir
# include <string.h>				// strerror
# include <errno.h>
# include <sys/ioctl.h>				// ioctl
# include <signal.h>				// signal, kill, sigaction, sigemptyset
# include <readline/readline.h>		// readline
# include <readline/history.h>
# include <stdbool.h>

# include "colors.h"
# include "../libft/libft.h"
# include "utils.h"
# include "check.h"
typedef	struct s_env
{
	char	**vars;
}	t_env;

void	setup_signal(void);

# endif
