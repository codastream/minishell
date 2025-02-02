#include "shell.h"

void	safe_dup2(t_data *data, int fdfrom, int fdto)
{
	int	code;

	code = dup2(fdfrom, fdto);
	handle_code(data, code, "dup error");
	close(fdfrom);
}

void	safe_pipe(t_data *data, int	fds[2])
{
	int	code;

	code = pipe(fds);
	handle_code(data, code, "pipe error");
}

int	safe_fork(t_data *data)
{
	int	child_pid;

	child_pid = fork();
	handle_code(data, child_pid, "fork error");
	return (child_pid);
}
