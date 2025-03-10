#ifndef DEBUG_H
# define DEBUG_H

#include "shell.h"

void	print_fd(t_data *data, t_exec *exec);
void	print_tokens(t_token **tokens);

void	print_tree(t_tree *root);
void	print_pretty_tree(t_data *data, t_tree *tree, int level, char *prefix, bool show_pipe_fds);
char	*get_token_type(t_tokentype type);

#endif
