#ifndef VAR_H
# define VAR_H

# define LAST_RETURN_CODE "?"

void	init_vars(t_data *data, char **env);
char	**hashtab_to_tab(t_data *data, t_hash *hash);

// return_code
void	update_last_return(t_data *data, int code);
int		get_last_return(t_data *data);

// expand
int		expand_vars(t_data *data, t_token **tokens, t_token *token);
char	*try_replace_vars(t_data *data, char *s, int *exp_idx, int mode);
bool	next_expand(char *string, char marker, int *i, bool *in_dquote);

int	handle_wilcard(t_data *data, t_token **tokens, t_token *token);

#endif
