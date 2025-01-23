#include "../../includes/shell.h"

/*
 * generates prompt with format $USERNAME@shellname>
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
	check_malloc(elems);
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
	check_malloc(prompt);
	free(elems);
	return (prompt);
}
