#ifndef VAR_H
# define VAR_H

# define LAST_RETURN_CODE "?"

void	init_vars(t_data *data, char **env);
char	**hashtab_to_tab(t_data *data, t_hash *hash);
void	update_last_return(t_data *data, int code);
int		get_last_return(t_data *data);
int		expand_vars(t_data *data, t_token **tokens, t_token *token);

# endif
