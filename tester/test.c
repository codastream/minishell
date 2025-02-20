#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/includes/libft.h"

# define MINISHELL_PATH "../minishell"

char	*build_instruction(char shell_type, char *test)
{
	char **ins_parts;
	char *instruction;

	ins_parts = ft_calloc(5, sizeof(char *));
	ins_parts[0] = "echo -e \"";
	ins_parts[1] = test;
	ins_parts[2] = "\n\" | ";
	if (shell_type == 'm')
		ins_parts[3] = MINISHELL_PATH;
	else
		ins_parts[3] = "bash";
	instruction = ft_multistrjoin(4, ins_parts, "");
	return (instruction);
}

void	print_stream(FILE *out)
{
	char	buffer[1000];
	while (fgets(buffer, sizeof(buffer)-1, out))
	{
		printf("%s", buffer);
	}
}

void	do_tests_for_file(int fd)
{
	char	*test;
	int		return_mini;
	// int		return_bash;
	// char	*output_mini;
	// char	*output_bash;
	FILE	*outstream;
	char	*instruction_m;
	// char	*instruction_b;

	test = get_next_line(fd);
	while (test)
	{
		instruction_m = build_instruction('m', test);
		return_mini = system(instruction_m);
		outstream = popen(instruction_m, "r");
		printf("%d\n", return_mini);
		print_stream(outstream);
		pclose(outstream);
		free(test);
		test = get_next_line(fd);
	}
	free(test);
}

int main()
{
	char	**test_files;
	int		i;
	int		fd;

	test_files = ft_calloc(2, sizeof(char *));
	test_files[0] = "syntax";
	i = 0;
	while (test_files[i])
	{
		fd = open(test_files[i], O_RDONLY);
		do_tests_for_file(fd);
		close(fd);
	}
}

