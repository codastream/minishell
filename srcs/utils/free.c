#include "shell.h"

void	reset(void *allocated)
{
	if (allocated)
	{
		free(allocated);
		allocated = NULL;
	}
}

void	free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->command_args)
		ft_free_2d_char_null_ended(command->command_args);
	if (command->command_name)
		reset(command->command_name);
	if (command->pathname)
		reset(command->pathname);
	if (command->redir_in)
		ft_lstclear(&command->redir_in, free);
	if (command->redir_out_append)
		ft_lstclear(&command->redir_out_append, free);
	if (command->redir_out_truncate)
		ft_lstclear(&command->redir_out_truncate, free);
	if (command->heredoc)
		ft_lstclear(&command->heredoc, free);
	reset(command);
}

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->builtins)
		free(exec->builtins);
	if (exec->builtin_ptrs)
		free(exec->builtin_ptrs);
	reset(exec);
}

void	free_token(t_token *token)
{
	if (token->command)
		free_command(token->command);
	if (token->string)
		reset(token->string);
	reset(token);
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*tmp;

	if (!tokens)
		return ;
	// print_tokens(tokens);
	if (*tokens)
	{
		current = tokens[0];
		while (current)
		{
			tmp = current->next;
			free_token(current);
			current = tmp;
		}
	}
	reset(tokens);
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->right)
		free_tree(tree->right);
	if (tree->left)
		free_tree(tree->left);
	free_token(tree->value);
	reset(tree);
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
	free(data->prompt);
	data->prompt = NULL;
}

void	free_data(t_data *data)
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

void	free_delimiters(t_delimiter **delims)
{
	int		i;

	i = 0;
	while (delims[i])
	{
		free(delims[i]->opening);
		free(delims[i]->closing);
		free(delims[i]);
		i++;
	}
	free(delims);
}
