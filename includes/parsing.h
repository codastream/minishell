#ifndef PARSING_H
# define PARSING_H

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
}	t_command;

typedef struct s_token t_token;
typedef struct s_token
{
	int			index;
	char		*string;
	t_command	*command;
	t_tokentype	type;
	t_token		*prev;
	t_token		*next;
}	t_token;

// lexer.c
void	do_for_tokens(t_token **tokens, void (*f)(t_token **, t_token *));
t_token	**tokenize(char *line);

// sanitize
void	add_after_splitted_on_space(t_token *token, int index_space);
void	merge_word_with_next_literal(t_token **tokens, t_token *token);
t_token	*get_first_of_consecutive(t_token *token);

// token utils
t_token	*new_token(t_tokentype type, int index, char *string);
void	add_before(t_token **tokens, t_token *current, t_token *new);
void	add_after(t_token *current, t_token *new);
void	add_token_back(t_token **tokens, t_token *new);

void	delete_token(t_token **tokens, t_token *token);
void	merge_with_next(t_token **tokens, t_token *token);
void	add_previous_redirect_to_command(t_token **tokens, t_token *command);
void	add_following_redirect_to_command(t_token **tokens, t_token *command);

// checking and tagging
t_command *new_command(char *string);
void	check_redirection(t_token **tokens, t_token *token);
void	check_pipe(t_token **tokens, t_token *token);
void	check_closing_quotes(char *input);
void	check_simple_command(t_token **tokens, t_token *token);

#endif
