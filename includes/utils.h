#ifndef UTILS_H
# define UTILS_H

// prompt.c
void	update_prompt(t_data *data);
char	*read_from_secondary(t_data *data, char *prompt, char closing, char *line);

// errors.c
void	printerr(char *msg);
void	check_alloc(t_data *data, void *allocated);
void	handle_and_exit_if_negative(t_data *data, int code, char *msg);

void	handle_strerror(t_data *data, char *error_source, int code, bool should_exit);
void	handle_custom_error(t_data *data, char *msg, int code, bool should_exit);
void	handle_custom_error_source_exit(t_data *data, char *error_source, char *msg, int code);
void	handle_custom_error_exit(t_data *data, char *error_source, char *msg, int code);
void	handle_custom_error_source(t_data *data, char *error_source, int code, bool should_exit);
void	handle_custom_error_source_noexit(t_data *data, char *error_source, char *msg, int code);

// void	handle_child_error(t_data *data, t_command *command);
void	handle_quote_error(t_data *data);
void	handle_command_not_found(t_data *data, char *msg, char *cmd, int code);
void	handle_builtin_error(t_data *data, t_command *command, char *msg, int code);
void	handle_syntax_error(t_data *data, char *token_str);

void	handle_end_of_loop(t_data *data);
void	handle_non_interactive_end(t_data *data, char *step);

char	*build_wrongvar_msg(t_data *data, char *error_source, char *wrong_var, char *msg);

// free.c
void	reset(void *allocated);
void	free_command(t_command *command);
void	free_token(t_token *token);
void	free_tokens(t_token **tokens);
void	free_exec(t_exec *exec);
void	free_tree(t_tree *tree);
void	free_vars_and_data(t_data *data);
void	free_after_exec(t_data *data);
void	free_all_data(t_data *data);
void	free_after_parsing(t_data *data);
void	free_delimiters(t_delimiter **delims);
void	free_before_parsing(t_data *data);

// init.c
t_data *init_data(char **env);

#endif
