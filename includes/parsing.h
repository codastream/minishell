#ifndef PARSING_H
# define PARSING_H

typedef enum e_token
{
	T_WORD,				// default
	T_PIPE,				// |
	T_LITERAL_SINGLE,
	T_LITERAL_DOUBLE,
	T_REDIRECT,			// during syntax checking < > << >>
	T_FILE				// during syntax checking
}	t_tokentype;

typedef struct s_token t_token;
typedef struct s_token
{
	int			index;
	char		*string;
	t_tokentype	type;
	t_token		*prev;
	t_token		*next;
}	t_token;

t_token	**tokenize(char *line);
void	print_tokens(t_token **tokens); // debug - to delete when ready

#endif
