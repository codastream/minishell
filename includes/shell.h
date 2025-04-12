/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:22:36 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 22:01:08 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>				// malloc, free, getenv
# include <fcntl.h>					// open, close
# include <stdio.h>					// printf
# include <unistd.h>				// fork, execve, access, dup, dup2, ...
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

# include "../libft/includes/libft.h"
# include "colors.h"
# include "structs.h"
# include "builtins.h"
# include "parsing.h"
# include "signals.h"
# include "utils.h"
# include "debug.h"
# include "errors.h"
# include "exec.h"
# include "var.h"
# include "fds.h"
# include "wildcard_bonus.h"

# define PRINT 0
# define PRINTFD 0

#endif
