#include "shell.h"

void	update_last_return(t_data *data, int code)
{
	char	*code_s;

	code_s = ft_itoa(code);
	check_alloc(data, code_s);
	ft_hash_update(data->localvars, LAST_RETURN_CODE, code_s);
	free(code_s);
}

int	get_last_return(t_data *data)
{
	int		code;
	char	*code_str;

	code_str = ft_hash_get(data->localvars, LAST_RETURN_CODE);
	code = ft_atoi(code_str);
	return (code);
}
