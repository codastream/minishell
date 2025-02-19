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
		reset(command->redir_in);
	if (command->redir_out_append)
		reset(command->redir_out_append);
	if (command->redir_out_truncate)
		reset(command->redir_out_truncate);
	if (command->heredoc)
		reset(command->heredoc);
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
  // free_token(tree->value);
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
		free_tokens(data->tokens);
	if (data->tree)
		free_tree(data->tree);
	if (data->exec)
		free_exec(data->exec);
	if (data->varstab)
		ft_free_2d_char_null_ended(data->varstab);
	reset(data->line);
	reset(data->prompt);
}

void	free_data(t_data *data)
{
	ft_free_hashtable(data->vars);
	reset(data);
}
