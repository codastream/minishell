/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:14:49 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/02 17:33:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_data	*init_data(char **env)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->prompt = NULL;
	init_vars(data, env);
	return (data);
}

static void	fill_builtin_names(char **builtins)
{
	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "exit";
	builtins[3] = "env";
	builtins[4] = "pwd";
	builtins[5] = "unset";
	builtins[6] = "export";
}

void	init_builtins(t_data *data, t_exec *exec)
{
	char		**builtins;
	t_builtin	*builtin_f;

	builtins = ft_calloc(8, sizeof(char *));
	if (!builtins)
		free(exec);
	check_alloc(data, builtins);
	fill_builtin_names(builtins);
	exec->builtins = builtins;
	builtin_f = ft_calloc(8, sizeof(t_builtin *));
	if (!builtin_f)
	{
		free(builtins);
		free(exec);
	}
	check_alloc(data, builtin_f);
	builtin_f[0] = ft_cd;
	builtin_f[1] = ft_echo;
	builtin_f[2] = ft_exit;
	builtin_f[3] = ft_env;
	builtin_f[4] = ft_pwd;
	builtin_f[5] = ft_unset;
	builtin_f[6] = ft_export;
	exec->builtin_ptrs = builtin_f;
}

t_exec	*init_exec(t_data *data, t_tree *tree)
{
	t_exec		*exec;
	int			count;

	exec = ft_calloc(1, sizeof(t_exec));
	check_alloc(data, exec);
	init_builtins(data, exec);
	count = 0;
	iter_tree_count(tree, &count, count_if_command);
	exec->commands_nb = count;
	exec->current_cmd_index = 0;
	return (exec);
}

