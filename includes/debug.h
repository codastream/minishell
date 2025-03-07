#ifndef DEBUG_H
# define DEBUG_H

#include "shell.h"

void	print_tokens(t_token **tokens);
char	*get_token_type(t_tokentype type);
void	print_tree(t_tree *root);
void	debug_fd(t_data *data, t_exec *exec);
void	print_fd(t_data *data);

#endif
