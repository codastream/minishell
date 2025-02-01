#include "shell.h"

void	safe_dup2(int fdfrom, int fdto)
{
	int	code;

	code = dup2(fdfrom, fdto);
	handle_code(code, "dup error");
	close(fdfrom);
}

void	safe_pipe(int	fds[2])
{
	int	code;

	code = pipe(fds);
	handle_code(code, "pipe error");
}

int	safe_fork(void)
{
	int	child_pid;

	child_pid = fork();
	handle_code(child_pid, "fork error");
	return (child_pid);
}
