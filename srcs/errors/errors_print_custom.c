#include "shell.h"

void	printerr_command_notfound(char *command_name)
{
	ft_printfd(2, "%sCommand '%s' not found%s\n", P_RED, command_name, P_NOC);
}

void	printerr_syntax(char *tokenstr)
{
	ft_printfd(2, "%ssyntax error near unexpected token `%s'%s\n", P_RED, tokenstr, P_NOC);
}

