#include "shell.h"

void	reset(void *allocated)
{
	if (allocated)
	{
		free(allocated);
		allocated = NULL;
	}
}

void	free_delimiters(t_delimiter **delims)
{
	int		i;

	i = 0;
	while (delims[i])
	{
		free(delims[i]->opening);
		free(delims[i]->closing);
		free(delims[i]);
		i++;
	}
	free(delims);
}
