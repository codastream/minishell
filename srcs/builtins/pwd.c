#include "shell.h"

char	*getpwd(t_data *data)
{
	int		size;
	char	*buffer;

	size = 2048;
	buffer = malloc(size);
	check_alloc(data, buffer);
	while (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		size = size * 2;
		buffer = malloc(size);
	}
	return (buffer);
}

void	ft_pwd(t_data *data, t_token *token)
{
	int		size;
	char	*buffer;

	(void) data;
	size = 2048;
	buffer = malloc(size);
	check_alloc(data, buffer);
	while (getcwd(buffer, size) == NULL)
	{
		free(buffer);
		size = size * 2;
		buffer = malloc(size);
		check_alloc(data, buffer);
	}
	ft_printfd(token->out, "%s\n", buffer);
	free(buffer);
}
