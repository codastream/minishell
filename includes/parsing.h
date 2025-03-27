/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:00:37 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 17:53:08 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "shell.h"

// lexer.c
int			do_for_tokens(t_data *data, t_token **tokens, \
				int (*f)(t_data *, t_token **, t_token *));
int			tokenize(t_data *data, char *line);

// token utils
int			get_tokens_nb(t_token **tokens);
t_token		*get_last(t_token **tokens);
bool		is_file(t_token *token);
bool		is_redir_operator(t_token *token);
void		delete_token(t_token **tokens, t_token *token);

// token utils create
t_token		*new_token(t_data *data, t_tokentype type, int index, \
				char *string);
void		add_token_back(t_token **tokens, t_token *new);
void		add_before(t_token **tokens, t_token *current, t_token *new);
void		add_after(t_token *current, t_token *new);
void		split_append_token(t_data *data, t_token *token, int index_space, \
				t_tokentype filetype);

// split utils
char		**init_separators_for_operators(t_data *data);
t_delimiter	**init_quote_delimiters(t_data *data);

// path utils
bool		is_path(char *s);
bool		is_absolute_path(char *s);
char		*find_in_paths(t_data *data, char **splitted_paths, char *name);

// checking
char		*get_checked_pathmame(t_data *data, t_command *command);
int			check_pipe(t_data *data, t_token **tokens, t_token *token);
int			check_closing_quotes(t_data *data, char *input);
int			check_closing_doublequotes(t_data *data, char *input);
int			check_redirection(t_data *data, t_token **tokens, \
				t_token *token);

// check files

bool		is_elf_executable(t_data *data, char *path);
bool		is_script(t_data *data, char *path);

// command utils
int			update_command_from_extra_words_before_pipe(t_data *data, \
				t_token **tokens, t_token *token);
void		update_command_from_string(t_data *data, t_command *command, \
				char *string);
t_command	*new_command(t_data *data, char *string);
t_list		**get_redir_list_from_operator(t_token *operator_token, \
				t_token *command_token);
void		add_redirect_file_to_command(t_data *data, t_token **tokens, \
				t_token *command_token, t_token *file_token);

void		add_command_to_token(t_data *data, t_token **tokens, \
			t_token *token);

// command
int			add_command_from_word(t_data *data, t_token **tokens, \
				t_token *token);
t_token		*add_command_from_redirop(t_data *data, t_token **tokens, \
				t_token *token, t_token *next);
t_token		*remove_extra_command(t_data *data, t_token **tokens, \
				t_token *token, t_token *next);

// trim
void		handle_quote_in_arg(t_data *data, char **arg);
int			handle_quotes(t_data *data, t_token **tokens, t_token *token);

// args
int			remove_empty_args(t_data *data, t_token **tokens, \
				t_token *token);

#endif
