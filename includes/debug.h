/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:01:04 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 15:06:41 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "shell.h"

void	print_fd(t_data *data, t_exec *exec);
void	print_tokens(t_token **tokens);

void	print_datafds(t_data *data);
void	print_tree(t_tree *root);
void	print_pretty_tree(t_data *data, t_tree *tree, int level, char *prefix);
char	*get_token_type(t_tokentype type);

#endif
