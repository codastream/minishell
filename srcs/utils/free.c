#include "shell.h"

void	free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->command_args)
		ft_free_2d_char_null_ended(command->command_args);
	if (command->command_name)
		free(command->command_name);
	if (command->pathname)
		free(command->pathname);
	if (command->redir_in)
		free(command->redir_in);
	if (command->redir_out_append)
		free(command->redir_out_append);
	if (command->redir_out_truncate)
		free(command->redir_out_truncate);
	if (command->heredoc)
		free(command->heredoc);
	free(command);
}


void	free_exec(t_exec *exec)
{
	free(exec);
}

void	free_token(t_token *token)
{
	if (token->command)
		free_command(token->command);
	if (token->string)
		free(token->string);
	free(token);
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*tmp;

	current = *tokens;
	while (current)
	{
		tmp = current->next;
		free_token(current);
		current = tmp;
	}
	free(tokens);
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->right)
		free_tree(tree->right);
	if (tree->left)
		free_tree(tree->left);
	if (tree->value)
		free_token(tree->value);
	free(tree);
}
void	free_after_exec(t_data *data)
{
	if (data->tokens)
		free(data->tokens);
	if (data->tree)
		free_tree(data->tree);
	if (data->exec)
		free_exec(data->exec);
	if (data->line)
		free(data->line);
}

void	free_data(t_data *data)
{
	free_after_exec(data);
	free(data->prompt);
	free(data);
}
