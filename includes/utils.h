#ifndef UTILS_H
# define UTILS_H

// prompt.c
void	update_prompt(t_data *data);
char	*read_from_secondary(t_data *data, char *prompt, char closing, char *line);

// errors.c
void	printerr(char *msg);
void	check_alloc(t_data *data, void *allocated);
void	handle_syntax_error(t_data *data, char *token_str);
void	handle_error(t_data *data, char *msg);
void	handle_code(t_data *data, int code, char *msg);
void	handle_invalid_command(t_data *data);

// free.c
void	free_command(t_command *command);
void	free_token(t_token *token);
void	free_tokens(t_token **tokens);
void	free_exec(t_exec *exec);
void	free_tree(t_tree *tree);
void	free_data(t_data *data);
void	free_after_exec(t_data *data);

// init.c
t_data *init_data(char **env);

#endif
