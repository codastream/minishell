#include "shell.h"

void	process_input(t_data *data, t_command *command, int fds[2])
{
	char	*input;

	close(fds[0]);
	input = get_next_line(data->exec->original_in);
	while (input && ft_strcmp(input, command->heredoc))
	{
		ft_print_str_fd(fds[1], input);
		free(input);
		input = get_next_line(data->exec->original_in);
	}
	free(input);
	close(fds[1]);
}

void	init_heredoc(t_data *data, t_token *token)
{
	int		fds[2];
	int		child_pid;

	if (!token->command->heredoc)
		return ;
	safe_pipe(data, fds);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		process_input(data, token->command, fds);
	}
	else
	{
		data->exec->last_pid = child_pid;
		token->in = dup(fds[0]);
	}
}
