#include "../../includes/shell.h"

/*
 * displays an error msg on stderr with red text
 */
void	printerr(char *msg)
{
	//ft_printfd(2, "%s%s%s\n", P_RED, msg, P_NOC);
	ft_printf("%s%s%s\n", P_RED, msg, P_NOC);
}

void	handle_error(char *msg)
{
	printerr(msg);
	// free previously allocated
	exit(EXIT_FAILURE);
}

void	check_malloc(void *allocated)
{
	if (!allocated)
		handle_error("memory allocation error");
}
