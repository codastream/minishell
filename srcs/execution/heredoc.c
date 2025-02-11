#include "shell.h"

void	init_heredoc(t_data *data, t_token *token)
{
	int		fds[2];
	int		child_pid;
	char	*input;

	if (!token->command->heredoc)
		return ;
	safe_pipe(data, fds);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		input = get_next_line()
	}
	else
	{
		data->exec->last_pid = child_pid;
		token->in = dup(fds[0]);
	}
}
