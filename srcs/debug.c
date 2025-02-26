#include "shell.h"

void	debug_fd(t_data *data, t_exec *exec)
{
	(void) data;
	printf("\t---fds\n");
	printf("\tcommand # %d\n", exec->current_cmd_index);
	printf("\tfuture_redirin %d\n", exec->future_redirin);
	printf("\tfds read end %d\n", exec->fds[0]);
	printf("\tfds write end %d\n", exec->fds[1]);
	printf("\toriginal in %d and out %d\n", exec->original_in, exec->original_out);
	printf("\t---\n");
}

char	*get_token_type(t_tokentype type)
{
	if (type == T_WORD)
		return ("word");
	else if (type == T_PIPE)
		return ("pipe");
	else if (type == T_LITERAL_SINGLE)
		return ("single quote literal");
	else if (type == T_LITERAL_DOUBLE)
		return ("double quote literal");
	else if (type == T_REDIR_HEREDOC)
		return ("redirect heredoc");
	else if (type == T_REDIR_IN)
		return ("redirect infile");
	else if (type == T_REDIR_TRUNCATE)
		return ("redirect outfile");
	else if (type == T_REDIR_APPEND)
		return ("redirect append");
	else if (type == T_EOF)
		return ("eof");
	else if (type == T_INFILE)
		return ("infile");
	else if (type == T_OUTFILE_APPEND)
		return ("outfile >>");
	else if (type == T_OUTFILE_TRUNCATE)
		return ("outfile >");
	else if (type == T_COMMAND)
		return ("command");
	else
		return ("unknown");
}

void	print_redirs(char *redirtype, t_list *redirlist)
{
	t_list	*current;

	current = redirlist;
	printf("\t\t%s%s : %s", P_GREEN, redirtype, P_NOC);
	while (current)
	{
		printf("%s %s%s", P_GREEN, (char *)current->content, P_NOC);
		current = current->next;
	}
	printf("\n");
}

void	print_command(t_command *command)
{
	int	i;

	printf("\t\t%scommand name\t:%s%s\n", P_PINK, command->command_name, P_NOC);
	printf("\t\t%sargs\t\t:%s", P_PINK, P_NOC);
	i = 0;
	while (command->command_args[i])
	{
		printf("%s%s|%s", P_PINK, command->command_args[i], P_NOC);
		i++;
	}
	printf("\n");
}

void	print_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		printf("token #%d\t", current->index);
		printf("%s%*s%s", P_BLUE, 15, current->string, P_NOC);
		printf("\t\ttype %s\n", get_token_type(current->type));
		if (current->type == T_COMMAND)
		{
			print_redirs("< in\t\t", current->command->redir_in);
			print_redirs("<< heredoc\t", current->command->heredoc);
			print_redirs(">> append\t", current->command->redir_out_append);
			print_redirs("> truncate\t", current->command->redir_out_truncate);
			print_command(current->command);
		}
		current = current->next;
	}
	printf("\n");
}

void	print_tree(t_tree *root)
{
	t_tree	*current;

	if (!root)
		return ;
	current = root;
	print_tree(current->left);
	if (current->left)
		printf("->");
	if (current->value)
		printf("%s%s%s (%s)", P_BLUE, current->value->string, P_NOC, get_token_type(current->value->type));
	if (current->left)
		printf("->");
	print_tree(current->right);
}
