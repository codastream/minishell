#include "shell.h"

void	safe_dup2(t_data *data, int fdfrom, int fdto)
{
	int	code;

	// printf("redir de %d -> %d\n", fdfrom, fdto);
	code = dup2(fdfrom, fdto);
	handle_and_exit_if_negative(data, code, "dup error");
	pop_fd(&data->fds, fdfrom);
}

void	safe_pipe(t_data *data, int	fds[2])
{
	int	code;

	code = pipe(fds);
	handle_and_exit_if_negative(data, code, "pipe error");
}

int	safe_fork(t_data *data)
{
	int	child_pid;

	child_pid = fork();
	handle_and_exit_if_negative(data, child_pid, "fork error");
	return (child_pid);
}
