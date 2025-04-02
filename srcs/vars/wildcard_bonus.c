/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmassavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:46:47 by jmassavi          #+#    #+#             */
/*   Updated: 2025/04/01 20:46:54 by jmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	cmd_char(char *rep, char *wildcard, int *i, int *j)
{
	if (wildcard[(*j)] == '*')
	{
		while (wildcard[(*j)] == '*')
			(*j)++;
		while (rep[(*i)] && (ft_strncmp(&rep[(*i)], &wildcard[(*j)], \
		len_wilcard(&wildcard[(*j)])) || !wildcard[(*j)]))
			(*i)++;
		if (!rep[(*i)] && wildcard[(*j)])
			return (0);
	}
	else if (rep[(*i)] != wildcard[(*j)])
	{
		if (wildcard[(*j)])
			return (0);
		while ((*j) > 0 && wildcard[(*j)] != '*')
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

int	wildcard_count_elem(char *str)
{
	int		i;
	int		len;
	char	**current_repository;

	i = 0;
	len = 0;
	current_repository = recover_current_repository(str[0]);
	while (current_repository[i])
	{
		if (ft_cmp_wildcard(current_repository[i++], str))
			len++;
	}
	ft_free_2d_char_null_ended(current_repository);
	return (len);
}

char	**ft_expand_wildcard(char *str)
{
	int		i;
	int		j;
	char	**wildcard;
	char	**current_repository;

	i = 0;
	j = 0;
	wildcard = ft_calloc(wildcard_count_elem(str) + 1, sizeof(char *));
	current_repository = recover_current_repository(str[0]);
	while (current_repository[i])
	{
		if (ft_cmp_wildcard(current_repository[i], str))
			wildcard[j++] = ft_strdup(current_repository[i]);
		i++;
	}
	ft_free_2d_char_null_ended(current_repository);
	return (wildcard);
}

int	handle_wilcard(t_data *data, t_token **tokens, t_token *token)
{
	char	*s;
	char	**expand_wildcard;
	int		i;

	(void)tokens;
	if (token->type != T_COMMAND || !token->command->command_args)
		return (EXIT_IGNORE);
	i = 0;
	while (token->command->command_args[i])
	{
		s = ft_strdup(token->command->command_args[i]);
		check_alloc(data, s);
		expand_wildcard = ft_expand_wildcard(s);
		join_wildcard(&s, expand_wildcard);
		if (!ft_isemptystr(s))
		{
			free(token->command->command_args[i]);
			token->command->command_args[i] = s;
		}
		else
			free(s);
		i++;
	}
	return (EXIT_SUCCESS);
}
