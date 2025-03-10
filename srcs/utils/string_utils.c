#include "shell.h"

void	skip_single_quote(char *string, int *i)
{
	(*i)++;
	while (string[*i] && string[*i] != '\'')
		(*i)++;
}
