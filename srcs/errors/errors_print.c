#include "shell.h"

/*
 * displays an error msg on stderr with red text
 */
void	printerr(char *msg)
{
	ft_printfd(2, "%s%s%s\n", P_RED, msg, P_NOC);
}

void	printerr_source(char *error_source, char *msg)
{
	ft_printfd(2, "%s%s: %s%s\n", P_RED, error_source, msg, P_NOC);
}

void	printerr_strno(void)
{
	ft_printfd(2, "%s%s%s\n", P_RED, strerror(errno), P_NOC);
}
void	printerr_strno_source(char *error_source)
{
	ft_printfd(2, "%s%s: %s%s\n", P_RED, error_source, strerror(errno), P_NOC);
}
