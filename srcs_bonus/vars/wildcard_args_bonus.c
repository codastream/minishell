/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_args_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:12:33 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/05 13:08:08 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**init_new_args(int *arg_size, int *exp_size, char **args, \
		char **expanded)
{
	char	**new_args;

	*arg_size = ft_count_2dchar_null_ended(args);
	*exp_size = ft_count_2dchar_null_ended(expanded);
	new_args = ft_calloc(*arg_size - 1 + *exp_size + 1, sizeof(char *));
	return (new_args);
}

void	copy_args(int *i, char **new_args, char **args, int index)
{
	*i = 0;
	while (*i < index)
	{
		new_args[*i] = args[*i];
		(*i)++;
	}
}

char	**insert_args_at_index(t_data *data, char **args, int *index, \
			char **expanded)
{
	int		arg_size;
	int		exp_size;
	char	**new_args;
	int		i;
	int		j;

	new_args = init_new_args(&arg_size, &exp_size, args, expanded);
	check_alloc(data, new_args);
	copy_args(&i, new_args, args, *index);
	j = 0;
	while (j < exp_size)
	{
		new_args[i + j] = expanded[j];
		j++;
	}
	free(args[i]);
	while (i + 1 < arg_size)
	{
		new_args[i + j] = args[i + 1];
		i++;
	}
	*index += exp_size - 1;
	return (new_args);
}

void	adjust_args(t_data *data, t_command *command, int *i, \
			char	**expanded)
{
	int		size;
	char	**new_args;

	if (!expanded)
		return ;
	if (!expanded[0])
	{
		ft_free_2d_char_null_ended(expanded);
		return ;
	}
	size = ft_count_2dchar_null_ended(expanded);
	if (size == 1)
	{
		free(command->command_args[*i]);
		command->command_args[*i] = ft_strdup(expanded[0]);
		free(expanded);
	}
	else
	{
		new_args = insert_args_at_index(data, command->command_args, i, \
			expanded);
		free(expanded);
		free(command->command_args);
		command->command_args = new_args;
	}
}
