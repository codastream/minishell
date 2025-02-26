#include "shell.h"

void	free_before_parsing(t_data *data)
{
	reset(data->line);
	reset(data->prompt);
}

void	free_after_parsing(t_data *data)
{
	ft_hash_remove(data->vars, LAST_RETURN_CODE);
	if (data->tokens)
		free_tokens(data->tokens);
	reset(data->line);
	reset(data->prompt);
}

void	free_after_exec(t_data *data)
{
	data->fds = NULL;
	if (data->tokens)
		free(data->tokens);
	if (data->tree)
		free_tree(data->tree);
	if (data->exec)
		free_exec(data->exec);
	if (data->varstab)
		ft_free_2d_char_null_ended(data->varstab);
	reset(data->line);
	reset(data->prompt);
}

void	free_vars_and_data(t_data *data) // can be replaced with free_all_data
{
	if (data->vars)
		ft_free_hashtable(data->vars);
	reset(data);
}

void  free_all_data(t_data *data)
{
  ft_free_hashtable(data->vars);
  if (data->fds)
    pop_all_fd(&data->fds);
  free_after_exec(data);
  free(data);
}
