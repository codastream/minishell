/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:40:15 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/10 19:16:16 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_file_str(t_data *data, t_token *file_token, bool *has_var)
{
	char	*redir_file_str;

	if (ft_strstr(file_token->string, "$"))
	{
		*has_var = true;
	}
	redir_file_str = ft_strdup(file_token->string);
	check_alloc(data, redir_file_str);
	return (redir_file_str);
}
