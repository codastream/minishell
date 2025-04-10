/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:37:59 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/10 21:16:39 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	copy_until_index(char **dest, char ***src, int *j, int index)
{
	while (*j != index)
	{
		dest[*j] = (*src)[*j];
		(*j)++;
	}
	free((*src)[index]);
}

void	insert_from_index(char **dest, char **result, int *j, int index)
{
	*j = 0;
	while (result[*j])
	{
		dest[index + *j] = result[*j];
		(*j)++;
	}
}

void	update_argc(t_token *token, int len)
{
	if (len > 1)
	{
		token->command->argc += (len - 1);
	}
}

void	copy_after_index(char **dest, char ***src, int *j, int i)
{
	while ((*src)[i])
	{
		dest[i + *j - 1] = (*src)[i];
		i++;
	}
}

void	split_in_expand(t_data *data, t_token *token, char ***arg, int i)
{
	int		len;
	int		j;
	char	**result;
	char	**args;

	j = 0;
	result = ft_split_str((*arg)[i], " \t\n\v\f");
	check_alloc(data, result);
	len = ft_count_2dchar_null_ended(result);
	update_argc(token, len);
	len = len + ft_count_2dchar_null_ended(*arg);
	args = ft_calloc(len, sizeof(char *));
	if (!args)
		free(result);
	check_alloc(data, args);
	copy_until_index(args, arg, &j, i);
	insert_from_index(args, result, &j, i);
	i++;
	copy_after_index(args, arg, &j, i);
	free(*arg);
	free(result);
	*arg = args;
}
