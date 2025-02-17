#include "shell.h"

void	process_input(t_data *data, t_command *command, int fds[2])
{
	char	*input;
  char  *eof;

	close(fds[0]);
	eof = ft_strjoin(command->heredoc, "\n");
	input = get_next_line(data->exec->original_in);
	while (input && ft_strcmp(input, eof))
	{
		ft_print_str_fd(fds[1], input);
		free(input);
		input = get_next_line(data->exec->original_in);
	}
	free(input);
  free(eof);
	close(fds[1]);
}

void	init_heredoc(t_data *data, t_tree **tree)
{
	int		fds[2];
	int		child_pid;

	if (!(*tree)->value->command->heredoc)
		return ;
	safe_pipe(data, fds);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		process_input(data, (*tree)->value->command, fds);
	}
  close(fds[1]);
  put_fd(data, tree, fds[0], (*tree)->value->out);
	waitpid(child_pid, NULL, 0);  
}
