/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:24:37 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/31 20:45:47 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	wait_all(t_data *data, t_exec *exec)
{
	int		status;
	pid_t	result;
	int		code;
	int		i;

	(void) data;
	code = EXIT_SUCCESS;
	i = 0;
	while (i < exec->commands_nb)
	{
		result = waitpid(0, &status, 0);
		if (result == exec->last_pid)
			code = WEXITSTATUS(status);
		i++;
	}
	return (code);
}

void	check_exec_builtin(t_data *data, t_tree *tree)
{
	int	code;

	code = iter_tree_token(data, tree, check_redirection_files);
	if (code == ERROR_EMPTY_REDIR)
		return ;
	if (!tree->value->command->has_invalid_redir)
		try_exec_builtin(data, tree->value, tree->value->command);
	return ;
}
