/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:46:47 by jmassavi          #+#    #+#             */
/*   Updated: 2025/04/09 22:19:07 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	cmd_char(char *rep, char *arg, int *i, int *j)
{
	if (arg[(*j)] == '*')
	{
		while (arg[(*j)] == '*')
			(*j)++;
		while (rep[(*i)] && (ft_strncmp(&rep[(*i)], &arg[(*j)], \
		len_wilcard(&arg[(*j)])) || !arg[(*j)]))
			(*i)++;
		if (!rep[(*i)] && arg[(*j)])
			return (0);
	}
	else if (rep[(*i)] != arg[(*j)])
	{
		if (arg[(*j)])
			return (0);
		while ((*j) > 0 && arg[(*j)] != '*')
			(*j)--;
		return (1);
	}
	if (rep[(*i)])
		(*i)++;
	(*j)++;
	return (1);
}

int	ft_cmp_wildcard(char *rep, char *wildcard)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (rep[i])
	{
		if (cmd_char(rep, wildcard, &i, &j) == 0)
			return (0);
	}
	return (1);
}

int	wildcard_count_elem(t_data *data, char *str)
{
	int		i;
	int		len;
	char	**current_repository;

	i = 0;
	len = 0;
	current_repository = recover_current_repository(data, str[0], str);
	while (current_repository && current_repository[i])
	{
		if (ft_cmp_wildcard(current_repository[i++], str))
			len++;
	}
	ft_free_2d_char_null_ended(current_repository);
	return (len);
}

char	**ft_expand_wildcard(t_data *data, char *str)
{
	int		i;
	int		j;
	char	**wildcard;
	char	**current_repository;

	i = 0;
	j = 0;
	wildcard = init_wildcard(data, str);
	if (!wildcard)
		return (wildcard);
	current_repository = recover_current_repository(data, str[0], str);
	while (current_repository && current_repository[i])
	{
		if (ft_cmp_wildcard(current_repository[i], str))
		{
			wildcard[j] = ft_strdup(current_repository[i]);
			if (!wildcard[j++])
				free_alloc_wildcardelem(data, wildcard, current_repository, \
					str);
		}
		i++;
	}
	ft_free_2d_char_null_ended(current_repository);
	sort_2dchar_null_ended(wildcard);
	return (wildcard);
}

int	handle_wilcard(t_data *data, t_token **tokens, t_token *token)
{
	char		*s;
	char		**expand_wildcard;
	int			i;
	bool		relative;

	(void)tokens;
	if (token->type != T_COMMAND || !token->command->command_args)
		return (EXIT_IGNORE);
	if (handle_wildcard_files(data, token) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (token->command->command_args[i])
	{
		relative = false;
		s = ft_strdup(token->command->command_args[i]);
		check_relatives(&s, &relative);
		check_alloc(data, s);
		expand_wildcard = ft_expand_wildcard(data, s);
		if (relative)
			s -= 2;
		free(s);
		adjust_args(data, token->command, &i, expand_wildcard);
		i++;
	}
	return (EXIT_SUCCESS);
}
