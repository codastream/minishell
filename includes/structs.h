/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:45:02 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/09 17:14:42 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/includes/libft.h"

typedef struct s_env
{
	char	**localvars;
}	t_env;

typedef struct s_fds
{
	int				fd;
	struct s_fds	*next;
}	t_fds;

typedef enum e_expandmode
{
	ARG,
	HEREDOC
}	t_expandmode;

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
	char		**command_args;
	int			argc;
	t_list		*redirections;
	t_list		*redir_in;
	t_list		*heredoc;
	t_list		*redir_out_truncate;
	t_list		*redir_out_append;
	bool		has_invalid_redir;
	bool		is_empty_command;
}	t_command;

typedef struct s_redir
{
	t_tokentype		type;
	char			*string;
	bool			ambiguous_redir;
}	t_redir;

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

typedef struct s_tree
{
	t_token			*value;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_data	t_data;
typedef void			(*t_builtin) (t_data *, t_token *);

typedef struct s_exec
{
	int			fds[2];
	int			commands_nb;
	int			current_cmd_index;
	int			last_pid;
	char		**builtins;
	char		*error_msg;
	t_builtin	*builtin_ptrs;
}	t_exec;

typedef struct s_data
{
	t_hash		*localvars;
	t_hash		*expvars;
	char		**varstab;
	t_token		**tokens;
	t_tree		*tree;
	t_exec		*exec;
	t_fds		*fds;
	char		*prompt;
	char		*line;
	int			heredoc_nb;
	int			return_code;
}	t_data;

#endif
