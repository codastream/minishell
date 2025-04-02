/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:34:37 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/02 17:35:55 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

int		handle_wilcard(t_data *data, t_token **tokens, t_token *token);
char	**ft_expand_wildcard(t_data *data, char *str);
int		wildcard_count_elem(t_data *data, char *str);

// utils
int		handle_wildcard_files(t_data *data, t_token *token);
char	**recover_current_repository(t_data *data, char hide, char *s);
void	join_wildcard(t_data *data, char **s, char **wildcard);
int		len_wilcard(char *str);
int		nb_files(t_data *data, char hide);

// free utils
void	free_joinwildcard(char **s, char **wildcard);

// init
char	**init_wildcard(t_data *data, char *str);
void	handle_failedadd(t_data *data, char **strs, char *s, DIR *dir);
void	free_alloc_wildcardelem(t_data *data, char **wildcard, \
			char **current_repository, char *str);

// args
char	**adjust_args(t_data *data, t_command *command, int i, \
			char	**expanded);

// sort
void	sort_2dchar_null_ended(char **elems);
char	**init_strs(t_data *data, char hide, char *s, int *nb);

#endif
