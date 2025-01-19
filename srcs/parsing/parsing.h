#ifndef PARSING_H
# define PARSING_H

typedef enum e_token
{
	T_COMMAND,
	T_PIPE,			// |
	T_REDIRECT,		// < > << >>
	T_OPERATOR,
	T_VAR			// $<var>
}	t_tokentype;

typedef struct s_lexer
{
	int		index;
	char	*string;
	t_tokentype	type;
	t_token	*prev;
	t_token	*next;
}	t_token;

void	tokenize(char *line);

#endif
