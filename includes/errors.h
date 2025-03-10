#ifndef ERRORS_H
# define ERRORS_H

# define EXIT_IGNORE 0
# define EXIT_SYNTAX_ERROR 2
# define EXIT_PERMISSION_DENIED 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NO_SUCH_FILE_OR_DIRECTORY 127
# define EXIT_HEREDOC_ERROR 130

# define MSG_MEMORY_ERROR "memory error"
# define MSG_FILENAME_ARGUMENT_REQUIRED "filename argument required"
# define MSG_SYNTAX_QUOTE_ERROR "unexpected EOF while looking for matching `\"'"
# define MSG_CMD_NOT_FOUND "command not found"
# define MSG_NO_SUCH_FILE_OR_DIRECTORY "No such file or directory"
# define MSG_TOO_MANY_ARGUMENTS "too many arguments"
# define MSG_NUMERIC_ARGUMENT_REQUIRED "numeric argument required"
# define MSG_NOT_VALID_IDENTIFIER "not a valid identifier"
# define MSG_IS_DIRECTORY "Is a directory"

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
void	handle_custom_error_source_exit(t_data *data, char *error_source, char *msg, int code);
void	handle_custom_error(t_data *data, char *msg, int code, bool should_exit);
void	handle_strerror(t_data *data, char *error_source, int code, bool should_exit);
void	handle_builtin_error(t_data *data, t_command *command, char *msg, int code);
void	handle_and_exit_if_negative(t_data *data, int code, char *msg);

// void	handle_custom_error_exit(t_data *data, char *error_source, char *msg, int code);
//void	handle_custom_error_source(t_data *data, char *error_source, int code, bool should_exit);
//void	handle_custom_error_source_noexit(t_data *data, char *error_source, char *msg, int code);
// void	handle_child_error(t_data *data, t_command *command);

// error util
char	*build_wrongvar_msg(t_data *data, char *error_source, char *wrong_var, char *msg);
void	update_last_error(t_data *data, int code);

#endif
