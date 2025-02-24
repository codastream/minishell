#ifndef PARSING_H
# define PARSING_H

# include "shell.h"

// lexer.c
int			do_for_tokens(t_data *data, t_token **tokens, int (*f)(t_data *, t_token **, t_token *));
int			tokenize(t_data *data, char *line);
t_delimiter	**init_quote_delimiters(t_data *data);

// sanitize
void	split_append_token(t_data *data, t_token *token, int index_space, t_tokentype filetype);
int	merge_word_with_next_literal(t_data *data, t_token **tokens, t_token *token);
void	merge_word_with_next_words(t_data *data, t_token **tokens, t_token *token);
int	merge_command_with_next_word(t_data *data, t_token **tokens, t_token *token);
t_token	*get_first_of_consecutive(t_token *token);

// token utils
int		get_tokens_nb(t_token **tokens);
t_token	*new_token(t_data *data, t_tokentype type, int index, char *string);
void	add_before(t_token **tokens, t_token *current, t_token *new);
void	add_after(t_token *current, t_token *new);
void	add_token_back(t_token **tokens, t_token *new);

void	delete_token(t_token **tokens, t_token *token);
void	merge_with_next(t_data *data, t_token **tokens, t_token *token);
bool	is_file(t_token *token);
bool	is_redir_operator(t_token *token);

// checking and tagging
int			check_closing_quotes(t_data *data, char *input);
int			check_redirection(t_data *data, t_token **tokens, t_token *token);
int			check_pipe(t_data *data, t_token **tokens, t_token *token);
char		*get_checked_pathmame(t_data *data, t_command *command);
int			check_simple_command(t_data *data, t_token **tokens, t_token *token);

// command
t_command	*new_command(t_data *data, char *string);
void		update_command_from_string(t_data *data, t_command *command, char *string);
void		add_previous_redirect_to_command(t_data *data, t_token **tokens, t_token *command);
void		add_following_redirect_to_command(t_data *data, t_token **tokens, t_token *command);
void		add_command_to_token(t_data *data, t_token **tokens, t_token *token, bool is_before_pipe);
void		add_empty_command_with_redir(t_data *data, t_token **tokens, t_token *token, bool is_before_pipe);

// expand
int		expand_in_words(t_data *data, t_token **tokens, t_token *token);
char	**split_skip_quotes(char *line);
int		handle_quote(t_data *data, t_token **tokens, t_token *token);


#endif
