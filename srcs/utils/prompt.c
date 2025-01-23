#include "shell.h"

/*
 * generates prompt string with format $USERNAME@shellname>
 */
char	*update_prompt(void)
{
	char	*username;
	char	**elems;
	char	*prompt;

	username = getenv("USER");
	if (!username)
		username = "user";
	elems = ft_calloc(10, sizeof(char *));
	check_alloc(elems);
	elems[0] = P_TEAL_BOLD_PROMPT;
	elems[1] = username;
	elems[2] = P_TEAL_LIGHT_PROMPT;
	elems[3] = "@";
	elems[4] = P_TEAL_BOLD_PROMPT;
	elems[5] = "C_shell";
	elems[6] = P_GREEN_PROMPT;
	elems[7] = " >";
	elems[8] = P_NOC_PROMPT;
	elems[9] = NULL;
	prompt = ft_strjoin(9, elems, "");
	check_alloc(prompt);
	free(elems);
	return (prompt);
}
char *read_from_secondary(char *prompt, char closing, char *line)
{
	char	*new_line;
	char	**new_lines;
	char	*joined;
	int		i;
	int		index_closing;
	char	*trimmed;

	i = 0;
	new_lines = ft_calloc(3, sizeof(char *));
	check_alloc(new_lines);
	new_lines[i++] = ft_strdup(line);
	free(line);
	while (true)
	{
		new_line = readline((const char *)prompt);
		index_closing = ft_strchri(new_line, closing);
		if (index_closing >= 0)
		{
			trimmed = ft_substr(new_line, 0, index_closing);
			check_alloc(trimmed);
			new_lines[i++] = trimmed;
			new_lines[i] = NULL;
			free(new_line);
			joined = ft_strjoin(i, new_lines, "");
			check_alloc(joined);
			ft_free_2d_char_null_ended(new_lines);
			return (joined);
		}
		else
		{
			new_lines[i] = ft_strdup(new_line);
			check_alloc(new_lines[i]);
			i++;
			free(new_line);
		}
	}
}
