/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:17:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/31 17:20:34 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_alloc_token(t_data *data, t_token *token, char **s)
{
	if (!token)
		ft_free_2d_char_null_ended(s);
	check_alloc(data, token);
}

void	check_alloc_tokens(t_data *data, t_token **tokens, char **s)
{
	if (!tokens)
		ft_free_2d_char_null_ended(s);
	check_alloc(data, tokens);
}
