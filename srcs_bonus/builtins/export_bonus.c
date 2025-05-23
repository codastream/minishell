/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:31:05 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/11 21:54:51 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**split_export_cmd(char *cmd)
{
	int		i;
	int		j;
	int		code;
	char	**result;

	i = 0;
	result = ft_calloc(4, sizeof(char *));
	if (!result)
		return (NULL);
	while (ft_ischarforenvvar(cmd[i]))
		i++;
	code = ft_strndup(&result[0], cmd, 0, i);
	if (!code)
	{
		ft_free_2d_char_null_ended(result);
	}
	j = i;
	while (i > 0 && cmd[i] && cmd[i - 1] != '=')
		i++;
	result = generate_export_split(result, cmd, i, j);
	return (result);
}

static void	print_according_to_value_presence(t_data *data, \
t_token *token, char *str)
{
	char	*result;

	result = ft_hash_get(data->localvars, str);
	if (result && str[0] != LAST_RETURN_CODE[0])
		ft_printfd(token->out, "declare -x %s=\"%s\"\n", str, \
		result);
	else if (str[0] != LAST_RETURN_CODE[0])
		ft_printfd(token->out, "declare -x %s\n", str);
}

void	ft_print_export(t_data *data, t_token *token)
{
	int		i;
	char	**str;

	(void)token;
	i = 0;
	str = hashtab_to_tab(data, data->localvars);
	sort_2dchar_null_ended(str);
	while (str[i])
		print_according_to_value_presence(data, token, str[i++]);
	ft_free_2d_char_null_ended(str);
}

void	pars_export(t_data *data, t_token *token, int i)
{
	char	**cmd;

	cmd = split_export_cmd(token->command->command_args[i]);
	check_alloc(data, cmd);
	if (ft_isenvvarkeystr(cmd[0]) && !ft_strcmp(cmd[1], "+="))
		append_export(data, cmd);
	else if (ft_isenvvarkeystr(cmd[0]) && !ft_strcmp(cmd[1], "="))
		supress_export(data, cmd);
	else if (ft_isenvvarkeystr(cmd[0]) && !cmd[1][0])
	{
		if (!ft_hash_get(data->localvars, cmd[0]))
			ft_hash_insert(data->localvars, cmd[0], NULL);
	}
	else if (token->command->command_args[i][0] == '-')
		update_last_return(data, EXIT_SYNTAX_ERROR);
	else
	{
		ft_printfd(2, "%sexport: `%s%s%s': not a valid identifier\n%s", \
			P_RED, cmd[0], cmd[1], cmd[2], P_NOC);
		update_last_return(data, EXIT_FAILURE);
	}
	ft_free_2d_char_null_ended(cmd);
}

void	ft_export(t_data *data, t_token *token)
{
	int		i;

	update_last_return(data, EXIT_SUCCESS);
	if (!token->command->command_args[1])
	{
		ft_print_export(data, token);
		return ;
	}
	i = 1;
	while (token->command->command_args[i])
	{
		if (!is_valid_identifier(token->command->command_args[i]))
		{
			ft_printfd(2, "%sexport: `%s': not a valid identifier\n%s", \
				P_RED, token->command->command_args[i], P_NOC);
			update_last_return(data, EXIT_FAILURE);
			break ;
		}
		pars_export(data, token, i++);
	}
}
