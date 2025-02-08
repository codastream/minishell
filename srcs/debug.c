#include "shell.h"

void	debug_fd(t_data *data, t_exec *exec)
{
	(void) data;
	printf("---fds\n");
	printf("future_redirin %d\n", exec->future_redirin);
	printf("fds read end %d\n", exec->fds[0]);
	printf("fds write end %d\n", exec->fds[1]);
	printf("original in %d and out %d\n", exec->original_in, exec->original_out);
	printf("---\n");
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
	else if (type == T_REDIR_OUT)
		return ("redirect outfile");
	else if (type == T_REDIR_APPEND)
		return ("redirect append");
	else if (type == T_FILE)
		return ("file");
	else if (type == T_COMMAND)
		return ("command");
	else
		return ("unknown");
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
			printf("\t\t%s<  in : %s\n%s", P_GREEN, current->command->redir_in, P_NOC);
			printf("\t\t%s<< heredoc : %s\n%s", P_GREEN, current->command->heredoc, P_NOC);
			printf("\t\t%s>  out: %s\n%s", P_GREEN, current->command->redir_out_truncate, P_NOC);
			printf("\t\t%s>> append: %s\n%s", P_GREEN, current->command->redir_out_append, P_NOC);
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
