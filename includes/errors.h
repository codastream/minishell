/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:01:06 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/08 23:10:19 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define EXIT_IGNORE 0
# define EXIT_SYNTAX_ERROR 2
# define EXIT_PERMISSION_DENIED 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NO_SUCH_FILE_OR_DIRECTORY 127
# define EXIT_HEREDOC_ERROR 130

# define ERROR_EMPTY_REDIR -1

# define MSG_MEMORY_ERROR "memory error"
# define MSG_FILENAME_ARGUMENT_REQUIRED "filename argument required"
# define MSG_SYNTAX_QUOTE_ERROR "unexpected EOF while looking for matching `\"'"
# define MSG_CMD_NOT_FOUND "command not found"
# define MSG_NO_SUCH_FILE_OR_DIRECTORY "No such file or directory"
# define MSG_TOO_MANY_ARGUMENTS "too many arguments"
# define MSG_NUMERIC_ARGUMENT_REQUIRED "numeric argument required"
# define MSG_NOT_VALID_IDENTIFIER "not a valid identifier"
# define MSG_IS_DIRECTORY "Is a directory"
# define MSG_PERMISSION_DENIED "Permission denied"
# define MSG_USAGE_NO_OPTS_NO_ARGS "usage : no OPTS and no ARGS"
# define MSG_USAGE_NO_OPTS "usage : no OPTS"

// errors alloc
void	check_alloc_token(t_data *data, t_token *token, char **s);
void	check_alloc_tokens(t_data *data, t_token **tokens, char **s);
void	check_alloc_varvalue(t_data *data, char **splitted, char **key, \
			char **value);

// error_print
void	printerr(char *msg);
void	printerr_source(char *error_source, char *msg);
void	printerr_strno(void);
void	printerr_strno_source(char *error_source);

// error_print_custom
void	printerr_command_notfound(char *command_name);
void	printerr_syntax(char *tokenstr);

// error_custom - for specific cases
void	handle_end_of_loop(t_data *data);
void	handle_non_interactive_end(t_data *data, char *step);
void	handle_quote_error(t_data *data);
void	handle_syntax_error(t_data *data, char *token_str);
void	check_alloc(t_data *data, void *allocated);

// error
void	handle_custom_error_source_noexit(t_data *data, char *error_source, \
			char *msg, int code);
void	handle_custom_error_source_exit(t_data *data, char *error_source, \
			char *msg, int code);
void	handle_custom_error_source_builtin(t_data *data, char *error_source, \
			char *msg, int code);
void	handle_custom_error(t_data *data, char *msg, int code, \
			bool should_exit);
void	handle_strerror(t_data *data, char *error_source, int code, \
			bool should_exit);
void	handle_and_exit_if_negative(t_data *data, int code, char *msg);

// error util
char	*build_wrongvar_msg(t_data *data, char *error_source, char *wrong_var, \
			char *msg);
void	update_last_error(t_data *data, int code);

#endif
