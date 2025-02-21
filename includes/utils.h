#ifndef UTILS_H
# define UTILS_H

// prompt.c
void	update_prompt(t_data *data);
char	*read_from_secondary(t_data *data, char *prompt, char closing, char *line);

// errors.c
void	printerr(char *msg);
void	check_alloc(t_data *data, void *allocated);
void	handle_syntax_error(t_data *data, char *token_str);
void	handle_fatal_error(t_data *data, char *msg, int code);
void	handle_code(t_data *data, int code, char *msg);
void  handle_child_error(t_data *data, t_command *command);
void	handle_quote_error(t_data *data);
void	handle_command_not_found(t_data *data, char *msg, char *cmd, int code);

// free.c
void	reset(void *allocated);
void	free_command(t_command *command);
void	free_token(t_token *token);
void	free_tokens(t_token **tokens);
void	free_exec(t_exec *exec);
void	free_tree(t_tree *tree);
void	free_data(t_data *data);
void	free_after_exec(t_data *data);
void  free_all_data(t_data *data);
void	free_after_parsing(t_data *data);

// init.c
t_data *init_data(char **env);

#endif
