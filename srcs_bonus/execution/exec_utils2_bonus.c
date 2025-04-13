/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:24:37 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/13 17:49:55 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	should_handle_signal(int status)
{
	int	signal;

	signal = WTERMSIG(status);
	if (signal == SIGINT || signal == SIGQUIT)
		return (true);
	return (false);
}

int	wait_all(t_data *data, t_exec *exec)
{
	int		status;
	pid_t	result;
	int		code;
	int		i;

	(void) data;
	code = EXIT_SUCCESS;
	i = 0;
	status = 0;
	while (i < exec->commands_nb)
	{
		result = waitpid(0, &status, 0);
		if (result == exec->last_pid)
		{
			// if (WIFEXITED(status))
			code = WEXITSTATUS(status);
			// if (WIFSIGNALED(status) && should_handle_signal(status))
			// 	code = 128 + WTERMSIG(status);
			if (PRINT == 1)
				printf("code is %d\n", code);
			return (code);
		}
		i++;
	}
	return (code);
}

void	check_exec_builtin(t_data *data, t_tree *tree)
{
	int	code;

	code = iter_tree_token(data, tree, prepare_heredoc);
	code = iter_tree_token(data, tree, prepare_redirs);
	if (code == ERROR_EMPTY_REDIR)
		return ;
	if (!tree->value->command->has_invalid_redir)
		try_exec_builtin(data, tree->value, tree->value->command);
	return ;
}

void	handdle_invalid_file(t_data *data, t_token *token, t_redir *redir)
{
	token->command->has_invalid_redir = true;
	if (redir->has_var)
	{
		printerr_source(redir->string, MSG_AMBIGUOUS_REDIRECT);
	}
	else if (access(redir->string, F_OK == -1))
	{
		printerr_source(redir->string, MSG_NO_SUCH_FILE_OR_DIRECTORY);
	}
	else
	{
		handle_strerror(data, redir->string, EXIT_FAILURE, false);
	}
	update_last_return(data, EXIT_FAILURE);
}
