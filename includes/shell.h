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
# include "../libft/includes/libft.h"

typedef	struct s_env
{
	char	**vars;
}	t_env;

typedef enum e_token
{
	T_COMMAND,
	T_WORD,				// default
	T_PIPE,				// |
	T_LITERAL_SINGLE,
	T_LITERAL_DOUBLE,
	T_REDIR_HEREDOC,
	T_REDIR_IN,
	T_REDIR_APPEND,
	T_REDIR_OUT,
	T_FILE,				// during syntax checking
	T_VAR
}	t_tokentype;

typedef struct s_command
{
	int			index;
	char		*command_name;
	char		*command_path;
	char		**command_args; // command name of path + options - null ended for execve
	char		*redir_in;
	char		*heredoc;
	char		*redir_out_truncate;
	char		*redir_out_append;
	bool		has_invalid_redir;
}	t_command;

typedef struct s_token
{
	int				index;
	char			*string;
	t_command		*command;
	t_tokentype		type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef	struct s_tree
{
	t_token			*value;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_exec
{
	int			fds[2];
	int			return_code;
	int			commands_nb;
	int			current_cmd_index;
	int			last_pid;
	int			future_fdin;
	t_command	**commands;
}	t_exec;

typedef struct s_data
{
	t_token		*tokens;
	t_tree		*tree;
}	t_data;

# include "tree.h"
# include "parsing.h"
# include "signals.h"
# include "utils.h"
# include "debug.h"
# include "errors.h"
# include "exec.h"

# endif
