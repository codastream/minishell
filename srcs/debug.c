#include "shell.h"

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
		printf("\ntoken #%d\n", current->index);
		printf("%s%s%s\n", P_BLUE, current->string, P_NOC);
		printf("type %s\n\n", get_token_type(current->type));
		current = current->next;
	}
}
