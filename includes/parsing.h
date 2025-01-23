#ifndef PARSING_H
# define PARSING_H

typedef enum e_token
{
	T_WORD,				// default
	T_PIPE,				// |
	T_LITERAL_SINGLE,
	T_LITERAL_DOUBLE,
	T_REDIR_HEREDOC,
	T_REDIR_IN,
	T_REDIR_APPEND,
	T_REDIR_OUT,
	T_FILE				// during syntax checking
}	t_tokentype;

typedef struct s_command
{
	int			index;
	char		*command_name;
	char		*command_path;
	char		**command_args; // command name of path + options - null ended for execve
	char		*redir_in;
	char		*redir_out;
}	t_command;

typedef struct s_token t_token;
typedef struct s_token
{
	int			index;
	char		*string;
	t_tokentype	type;
	t_token		*prev;
	t_token		*next;
}	t_token;

// lexer.c
t_token	**tokenize(char *line);
t_token	*new_token(t_tokentype type, int index, char *string);
void	print_tokens(t_token **tokens); // debug - to delete when ready
void	add_before(t_token **tokens, t_token *current, t_token *new);
void	do_for_tokens(t_token **tokens, void (*f)(t_token *));

// checker.c
void	check_redirection(t_token *token);

#endif
