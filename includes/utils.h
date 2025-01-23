#ifndef UTILS_H
# define UTILS_H

// prompt.c
char	*update_prompt(void);
char	*read_from_secondary(char *prompt, char closing, char *line);

// errors.c
void	printerr(char *msg);
void	check_alloc(void *allocated);
void	handle_syntax_error(char *token_str);

// free.c
void	free_tokens(t_token **tokens);

#endif
