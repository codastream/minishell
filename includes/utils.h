/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:00:55 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/10 17:31:08 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// loop.c
void	update_prompt(t_data *data);
void	process_line_input(t_data *data);

// free.c
void	free_command(t_command *command);
void	free_exec(t_exec *exec);
void	free_token(t_token *token);
void	free_tokens(t_token **tokens);
void	free_tree(t_tree *tree);

// free_combo
void	free_before_parsing(t_data *data);
void	free_after_parsing(t_data *data);
void	free_after_exec(t_data *data);
void	free_vars_and_data(t_data *data);
void	free_all_data(t_data *data);

// free_utils
void	reset(void *allocated);
void	free_delimiters(t_delimiter **delims);
void	free_redir_list(void *content);

// quote_utils
int		find_index_of_space_out_of_quotes(char *s);
void	skip_single_quote(char *string, int *i);
bool	is_quote(char c);
int		is_in_quotes(char *str);

// string utils 2
bool	is_empty_line(char *line);
bool	is_surrounded_by_pairofchar(char *s, char c);
int		ft_strndup(char **var, char *cmd, int start, int end);

// init.c
t_data	*init_data(char **env);
void	init_builtins(t_data *data, t_exec *exec);
t_exec	*init_exec(t_data *data, t_tree *tree);

// tree.c
t_tree	*make_tree(t_data *data, t_token *list);

// tree_util
int		iter_tree_count(t_tree *tree, int *count, \
			void (*f)(t_tree *, int *));
void	count_if_command(t_tree *tree, int *nb);
int		iter_tree_token(t_data *data, t_tree *tree, \
			int (*f)(t_data *data, t_token *token));

void	skip_quote(char	*string, int *i, char quote);

#endif
