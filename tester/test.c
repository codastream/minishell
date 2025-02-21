#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/includes/libft.h"

# define MINISHELL_PATH "../minishell"
// # define MINISHELL_PATH "./minishell"

char	*build_instruction(char shell_type, char *test, char *run_mode)
{
	char **ins_parts;
	char *instruction;

	ins_parts = ft_calloc(6, sizeof(char *));
	ins_parts[0] = "echo '";
	ins_parts[1] = test;
	ins_parts[2] = "' | ";
	if (shell_type == 'm')
		ins_parts[3] = MINISHELL_PATH;
	else
		ins_parts[3] = "bash";
	if (!ft_strcmp(run_mode, "system"))
		ins_parts[4] = " 2> /dev/null 1> /dev/null";
	else
		ins_parts[4] = " 2>&1";
	instruction = ft_multistrjoin(5, ins_parts, "");
	return (instruction);
}

void	print_stream_to_file(FILE *out, int fd)
{
	char	buffer[1000] = {0};
	while (fgets(buffer, sizeof(buffer)-1, out))
	{
		ft_printfd(fd, (const char *) buffer);
	}
}

void	print_stream_to_string(char shell, int ret, FILE *out, char *buffer)
{
	size_t n;

	(void) shell;
	(void) ret;
	n = fread(buffer, 1, 999, out);
	buffer[n] = '\0';
}
int	get_return_status(int ret_system)
{
	int ret;

	if (WIFEXITED(ret_system))
		ret = WEXITSTATUS(ret_system);
	else
		ret = -1;
	return (ret);
}

bool	have_same_return(int ret_b, int ret_m)
{
	if (ret_b != ret_m)
	{
		return (false);
	}
	return (true);
}

bool	have_same_output(int ret_b, int ret_m, char *buff_b, char *buff_m)
{
	char *bash_with_prompt;

	(void) ret_m;
	// only get first line for bash output
	char *newline = ft_strchr(buff_b, '\n');
	if (newline != NULL)
	{
		*newline = '\0';
	}
	newline = ft_strchr(buff_m, '\n');
	if (newline != NULL)
	{
		*newline = '\0';
	}

	// ignore red color for minishell error
	// if (ret_m != 0)
	// {
	// 	buff_m += ft_strlen("\\033[0;31");
	// }
	if (ret_b != 0)
	{
		bash_with_prompt = ft_strstr(buff_b, ": line ");
		if (bash_with_prompt)
		{
			bash_with_prompt += ft_strlen(": line ");
			while (*bash_with_prompt != ':')
				bash_with_prompt++;
			bash_with_prompt += 2;
			buff_b = bash_with_prompt;
		}
		if (ft_strstr(buff_m, buff_b))
			return (true);
		else
			return (false);
	}

	if (ft_strcmp(buff_b, buff_m))
	{
		return (false);
	}
	return (true);
}

void	do_tests_for_file(int fd, int *test_index, int *ok_count)
{
	char	*test;
	int		ret_system;
	int		ret_m;
	int		ret_b;
	char	*buff_m = ft_calloc(1000, sizeof(char));
	char	*buff_b = ft_calloc(1000, sizeof(char));
	FILE	*outstream_m;
	FILE	*outstream_b;
	char	*instruction_m;
	char	*instruction_popen_m;
	char	*instruction_b;
	char	*instruction_popen_b;
	bool	is_same_return = false;
	bool	is_same_output = false;

	test = get_next_line(fd);
	if (test && ft_strlen(test) > 0)
		test[ft_strlen(test) - 1] = '\0';
	while (test)
	{
		// ===== COMPARE RETURN
		instruction_m = build_instruction('m', test, "system");
		instruction_b = build_instruction('b', test, "system");
		ret_system = system(instruction_m);
		ret_m = get_return_status(ret_system);
		// printf("ret code %d\n", ret_m);
		ret_system = system(instruction_b);
		ret_b = get_return_status(ret_system);

		// ===== COMPARE OUTPUT
		instruction_popen_m = build_instruction('m', test, "popen");
		instruction_popen_b = build_instruction('b', test, "popen");
		outstream_m = popen(instruction_popen_m, "r");
		print_stream_to_string('m', ret_m, outstream_m, buff_m);
		outstream_b = popen(instruction_popen_b, "r");
		print_stream_to_string('n', ret_b, outstream_b, buff_b);
		pclose(outstream_m);
		pclose(outstream_b);

		// fd_outfile_m = open("mini_out", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		// if (fd_outfile_m < 0)
		// 	ft_printfd("%sErreur d'ouverture du fichier %s%s\n", P_RED, "mini_out", P_NOC);
		// close(fd_outfile_m);
		// printf("%s\n", buff_m);
		// print_stream_to_file(outstream_m, fd_outfile_m);
		// print_stream(outstream_m);

		// ===== COMPARE FILES


		// ===== DISPLAY
		printf("\n\n%d : ", *test_index);
		is_same_return = have_same_return(ret_b, ret_m);
		is_same_output = have_same_output(ret_b, ret_m, buff_b, buff_m);
		if ((is_same_return && is_same_output))
		{
			printf("✅");
			(*ok_count)++;
		}
		else
		{
			printf("❌");
		}
		printf("\t%50s\n", test);
		if (!is_same_output)
		{
			printf("❕ sortie\nbash:%s\nmini:%s\n", buff_b, buff_m);
		}

		if (!is_same_return)
		{
			printf("❕ valeurs de retour\nbash: %d\nmini:%d\n", ret_b, ret_m);
		}

		(*test_index)++;
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
	int		ok_count;
	int		test_count;

	ok_count = 0;
	test_count = 0;
	test_files = ft_calloc(3, sizeof(char *));
	test_files[0] = "vars";
	test_files[1] = "syntax";
	// test_files[0] = "tester/syntax";
	// test_files[1] = "tester/vars";

	i = 0;
	while (test_files[i])
	{
		fd = open(test_files[i], O_RDONLY, 0666);
		if (fd < 0)
			ft_printfd(2, "%sErreur d'ouverture du fichier %s%s\n", P_RED, test_files[i], P_NOC);
		do_tests_for_file(fd, &test_count, &ok_count);
		close(fd);
		i++;
	}
	if (ok_count == test_count)
	{
		printf("🎊 Success ");
		printf("%d out of %d tests passed", ok_count, test_count);
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("👷 Work still needed ");
		printf("%d out of %d tests passed", ok_count, test_count);
		return (EXIT_FAILURE);
	}
}

