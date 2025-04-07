/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:17:12 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/07 23:02:30 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	child_exec(t_data *data, t_command *command, t_token *token)
{
	char	**env_local;
	int		exec_code;

	env_local = hashtab_to_tab(data, data->localvars);
	check_alloc(data, env_local);
	data->varstab = env_local;
	if (!command->command_name || !command->command_args[0])
	{
		close(token->in);
		free_all_data(data);
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(command->command_name) == 0)
		handle_custom_error_source_exit(data, "", NULL, EXIT_CMD_NOT_FOUND);
	try_exec_builtin_in_fork(data, token, command);
	check_executable(data, token);
	safe_dup2(data, token->in, STDIN_FILENO);
	safe_dup2(data, token->out, STDOUT_FILENO);
	pop_all_fd(&data->fds);
	exec_code = execve((const char *) command->pathname, \
	command->command_args, env_local);
	handle_custom_error_source_exit(data, command->command_name, \
		strerror(errno), exec_code);
}

void	exec_command(t_data *data, t_tree *tree)
{
	int	child_pid;

	if (PRINT == 1)
		print_pretty_tree(data, data->tree, 0, "");
	setup_child_signal();
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (tree->value->command->has_invalid_redir)
		{
			close(data->exec->fds[1]);
			close(data->exec->fds[0]);
			free_all_data(data);
			exit(EXIT_FAILURE);
		}
		signal(SIGQUIT, SIG_DFL);
		child_exec(data, tree->value->command, tree->value);
	}
	else
		data->exec->last_pid = child_pid;
}

void	exec_pipe(t_data *data, t_tree *tree)
{
	int	fds[2];

	safe_pipe(data, fds);
	tree->value->pipe_read = fds[0];
	tree->value->pipe_write = fds[1];
	assign_fd(data, tree, tree->left, true);
	assign_fd(data, tree, tree->right, false);
	exec_tree_node(data, tree->left);
	if (PRINT == 1)
		print_pretty_tree(data, data->tree, 0, "");
	close(fds[1]);
	exec_tree_node(data, tree->right);
	close(fds[0]);
}

void	exec_tree_node(t_data *data, t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->value->type == T_PIPE)
	{
		exec_pipe(data, tree);
	}
	else if (tree->value->type == T_COMMAND)
	{
		exec_command(data, tree);
	}
}

void	exec_line(t_data *data, t_tree *tree)
{
	t_exec	*exec;
	int		code;

	exec = init_exec(data, tree);
	data->exec = exec;
	if (!tree->left && !tree->right && is_builtin(data, tree->value->command))
	{
		check_exec_builtin(data, tree);
		return ;
	}
	tree->value->in = 0;
	tree->value->out = 1;
	code = iter_tree_token(data, tree, check_redirection_files);
	exec_tree_node(data, tree);
	code = wait_all(data, data->exec);
	signal(SIGQUIT, SIG_IGN);
	pop_all_fd(&(data->fds));
	update_last_return(data, code);
	check_for_eof_and_signals(data);
}
