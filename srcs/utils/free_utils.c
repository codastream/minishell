/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:14:57 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 19:17:06 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	reset(void *allocated)
{
	if (allocated)
	{
		free(allocated);
		allocated = NULL;
	}
}

void	free_delimiters(t_delimiter **delims)
{
	int		i;

	i = 0;
	while (delims[i])
	{
		free(delims[i]->opening);
		free(delims[i]->closing);
		free(delims[i]);
		i++;
	}
	free(delims);
}

void	free_redir_list(void *content)
{
	t_redir	*redir;

	redir = (t_redir *)content;
	free(redir->string);
	redir->string = NULL;
}
