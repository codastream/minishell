#include "shell.h"

void	free_before_parsing(t_data *data)
{
	if (data->line)
		reset(data->line);
	data->line = NULL;
	if (data->prompt)
		reset(data->prompt);
	data->prompt = NULL;
}

void	free_after_parsing(t_data *data)
{
	free_before_parsing(data);
	if (data->tokens)
		free_tokens(data->tokens);
}

void	free_after_exec(t_data *data)
{
	free_before_parsing(data);
	if (data->fds)
		pop_all_fd(&data->fds);
	if (data->tokens)
		free(data->tokens);
	data->tokens = NULL;
	if (data->tree)
		free_tree(data->tree);
	data->tree = NULL;
	if (data->exec)
		free_exec(data->exec);
	data->exec = NULL;
	if (data->varstab)
		ft_free_2d_char_null_ended(data->varstab);
	data->varstab = NULL;
}

void	free_vars_and_data(t_data *data)
{
	if (data->vars)
		ft_free_hashtable(data->vars);
	reset(data);
}

void  free_all_data(t_data *data)
{
	free_after_exec(data);
	free_vars_and_data(data);
}
