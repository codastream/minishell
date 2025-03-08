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

# define PRINT 0
# define PRINTFD 0

typedef	struct s_env
{
	char	**vars;
}	t_env;

typedef struct s_fds
{
  int fd;
  struct s_fds  *next;
} t_fds;

typedef enum e_token
{
	T_AND,
	T_OR,
	T_PIPE,				// |
	T_COMMAND,
	T_OPENING_PARENTHESIS,
	T_CLOSING_PARENTHESIS,
	T_REDIR_HEREDOC,
	T_REDIR_IN,
	T_REDIR_APPEND,
	T_REDIR_TRUNCATE,
	T_WORD,				// default
	T_EOF,
	T_INFILE,
	T_OUTFILE_APPEND,
	T_OUTFILE_TRUNCATE,				// during syntax checking
	T_LITERAL_SINGLE,
	T_LITERAL_DOUBLE,
	T_VAR
}	t_tokentype;

typedef struct s_command
{
	int			index;
	char		*command_name;
	char		*pathname;
	char		**command_args; // command name of path + options - null ended for execve
	t_list		*redir_in;
	t_list		*heredoc;
	t_list		*redir_out_truncate;
	t_list		*redir_out_append;
	bool		has_invalid_redir;
	bool		is_empty_command;
}	t_command;

typedef struct s_token
{
	int				index;
	int				in;
	int				out;
	int				pipe_read;
	int				pipe_write;
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

typedef struct s_data t_data;
typedef void	(*t_builtin)(t_data *, t_token *);

typedef struct s_exec
{
	int			fds[2];
	int			commands_nb;
	int			current_cmd_index;
	int			last_pid;
	int			future_redirin;
	int			future_redirout;
	int			original_in;
	int			original_out;
	char		**builtins;
	char		*error_msg;
	t_builtin	*builtin_ptrs;

	// t_command	**commands;
}	t_exec;

typedef struct s_data
{
	t_hash		*vars;
	t_hash		*expvars;
	char		**varstab;
	t_token		**tokens;
	t_tree		*tree;
	t_exec		*exec;
  	t_fds     	*fds;
	char		*prompt;
	char		*line;
	int			return_code;
}	t_data;

# include "builtins.h"
# include "tree.h"
# include "parsing.h"
# include "signals.h"
# include "utils.h"
# include "debug.h"
# include "errors.h"
# include "exec.h"
# include "var.h"
# include "queue.h"
# include "fds.h"

# endif
