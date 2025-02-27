#include "shell.h"

void	safe_dup2(t_data *data, int fdfrom, int fdto)
{
	int	code;

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

void  put_fd_token(t_data *data, t_token *token, int in, int out)
{
	token->out = out;
	if (PRINTFD == 1)
		printf("-> %d\n-> %d\n\n", in, out);
	if (token->type == T_COMMAND && token->command->heredoc)
		fd_push_back(&(data->fds), in);
	else
	{
		token->in = in;
		fd_push_back(&(data->fds), in);
	}
	fd_push_back(&(data->fds), out);
	if (PRINTFD == 1)
		printf("in--> %d\n out-->%d\n\n", in, out);
	(void)data;
}

void  put_fd(t_data *data, t_tree **tree, int in, int out)
{
	(*tree)->value->out = out;
	if (PRINTFD == 1)
		printf("-> %d\n-> %d\n\n", in, out);
	if ((*tree)->value->type == T_COMMAND && (*tree)->value->command->heredoc)
		fd_push_back(&(data->fds), in);
	else
	{
		(*tree)->value->in = in;
		fd_push_back(&(data->fds), in);
	}
	fd_push_back(&(data->fds), out);
	if (PRINTFD == 1)
		printf("in--> %d\n out-->%d\n\n", in, out);
	(void)data;
}

void  close_all(t_tree *tree)
{
	if (tree->value->in < 0)
		close(tree->value->in);
	if (tree->value->out < 0)
		close(tree->value->out);
	if (tree->left)
		close_all(tree->left);
	if (tree->right)
	close_all(tree->right);
}
