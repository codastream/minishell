/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:34:37 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/02 13:24:20 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

int		handle_wilcard(t_data *data, t_token **tokens, t_token *token);
char	**ft_expand_wildcard(t_data *data, char *str);

int		handle_wildcard_files(t_data *data, t_token *token);
char	**recover_current_repository(t_data *data, char hide);
int		len_wilcard(char *str);
void	join_wildcard(t_data *data, char **s, char **wildcard);

void	sort_2dchar_null_ended(char **elems);

#endif
