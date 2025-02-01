#ifndef PARSING_H
# define PARSING_H



// lexer.c
void	do_for_tokens(t_token **tokens, void (*f)(t_token **, t_token *));
t_token	**tokenize(char *line);

// sanitize
void	add_after_splitted_on_space(t_token *token, int index_space);
void	merge_word_with_next_literal(t_token **tokens, t_token *token);
t_token	*get_first_of_consecutive(t_token *token);

// token utils
int		get_tokens_nb(t_token *tokens);
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
