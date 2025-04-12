/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:00:58 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/10 18:16:52 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
char	*try_replace_vars(t_data *data, char *s, int *exp_idx, \
			t_expandmode mode);
bool	next_expand(char *string, char marker, int *i, bool *in_dquote);
void	expand_vars_in_arg(t_data *data, t_token *token, char ***arg, int i);

// expand heredoc
void	expand_vars_in_heredoc(t_data *data, char **arg);

// expand redir

void	expand_var_in_redir(t_data *data, char	**file);
void	lst_iter_redir(t_data *data, t_list *lst, void (*f)(t_data *, char **));

// expand split
void	split_in_expand(t_data *data, t_token *token, char ***arg, int i);

// expand utils
void	toggle_quote_status(bool *in_dquote);
void	check_closing_dquotes(char *string, int *i, bool *in_dquote);
bool	check_in_dquote(char *s, char marker, int *i, bool *in_dquote);
void	check_out_dquote(char *s, int *i, bool *in_dquote);
void	reset_arg(char **arg);
int		compute_sublen(char *s, int *i, int len);
void	adjust_quote_status(char *expanded, char *s, int *last_expanded_index, \
			bool *in_dquote);

#endif
