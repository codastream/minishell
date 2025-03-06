#include "shell.h"

void	free_before_parsing(t_data *data)
{
	if (data->line)
		reset(data->line);
	if (data->prompt)
		reset(data->prompt);
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
	if (data->tree)
		free_tree(data->tree);
	if (data->exec)
		free_exec(data->exec);
	if (data->varstab)
		ft_free_2d_char_null_ended(data->varstab);
}

void	free_vars_and_data(t_data *data) // can be replaced with free_all_data
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
