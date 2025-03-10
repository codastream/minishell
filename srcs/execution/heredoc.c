#include "shell.h"

int g_signal = 0;

char *ft_strjoinfree(char *s1, char *s2)
{
  char  *str;

  str = ft_strjoin(s1, s2);
  free(s1);
  return(str);
}

void  put_fd_heredoc(t_data *data, t_tree **tree, int in, int out)
{
	(*tree)->value->in = in;
	(*tree)->value->out = out;
	fd_push_back(&(data->fds), in);
	fd_push_back(&(data->fds), out);
	(void)data;
}


void	process_input(t_data *data, t_command *command, int fds[2])
{
	char	*input;
	char	*eof;
	char	*expanded;
	int		last_expanded_index;

	last_expanded_index = 0;
	close(fds[0]);
	eof = ft_strjoin(command->heredoc->content, "\n");
	check_alloc(data, eof);
	while (true)
	{
		input = readline("> ");
		input = ft_strjoinfree(input, "\n");
		if (g_signal != 0 || !ft_strcmp(input, eof))
			break ;
		while (next_expand(input, '$', &last_expanded_index))
		{
			expanded = try_replace_vars(data, NULL, &last_expanded_index);
			free(input);
			input = expanded;
		}
		ft_print_str_fd(fds[1], input);
		free(input);
	}
	free(input);
	free(eof);
	close(fds[1]);
	free_all_data(data);
	(void) data;
	exit(132 - g_signal);
}

void	init_heredoc(t_data *data, t_tree **tree)
{
	int		fds[2];
	int		child_pid = 0;

	if (!(*tree)->value->command->heredoc)
		return ;
	safe_pipe(data, fds);
	child_pid = safe_fork(data);
	if (child_pid == 0)
	{
		setup_heredoc_signal();
		process_input(data, (*tree)->value->command, fds);
	}
	close(fds[1]);
	waitpid(child_pid, NULL, 0);
	put_fd_heredoc(data, tree, fds[0], (*tree)->value->out);
}

int heredoc_exec(t_data *data, t_tree **tree)
{
	if ((*tree)->left)
	{
		if (heredoc(data, &(*tree)->left) != 0)
			return (130);
	}
	if ((*tree)->right)
	{
		if (heredoc(data, &(*tree)->right) != 0)
			return (130);
	}
	if ((*tree)->value->type == T_COMMAND)
		init_heredoc(data, tree);
	return (g_signal);
}

int  heredoc(t_data *data, t_tree **tree)
{
  g_signal = 0;
  return (heredoc_exec(data, tree));
}
