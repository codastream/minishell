#include "shell.h"

char *ft_strjoinfree(char *s1, char *s2)
{
  char  *str;

  str = ft_strjoin(s1, s2);
  free(s1);
  return(str);
}

void	process_input(t_data *data, t_command *command, int fds[2])
{
	char	*input;
  char  *eof;

	close(fds[0]);
	eof = ft_strjoin(command->heredoc, "\n");
	input = readline(">");
  input = ft_strjoinfree(input, "\n");
	while (input && ft_strcmp(input, eof))
	{
		ft_print_str_fd(fds[1], input);
		free(input);
		input = readline(">");
    input = ft_strjoinfree(input, "\n");
	}
	free(input);
  free(eof);
	close(fds[1]);
  (void)data;
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
