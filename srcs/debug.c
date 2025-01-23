#include "shell.h"

char	*get_token_type(t_tokentype type)
{
	if (type == T_WORD)
		return ("0 - word");
	else if (type == T_PIPE)
		return ("1 - pipe");
	else if (type == T_LITERAL_SINGLE)
		return ("2 - single quote literal");
	else if (type == T_LITERAL_DOUBLE)
		return ("3 - double quote literal");
	else if (type == T_REDIR_APPEND || type == T_REDIR_HEREDOC || type == T_REDIR_IN || type == T_REDIR_OUT)
		return ("4 - redirect");
	else if (type == T_FILE)
		return ("5 - file");
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
