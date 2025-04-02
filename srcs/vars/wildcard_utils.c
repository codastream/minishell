/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:47:28 by jmassavi          #+#    #+#             */
/*   Updated: 2025/04/02 13:41:49 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	nb_files(t_data *data, char hide)
{
	int				i;
	struct dirent	*info_dir;
	DIR				*dir;
	char			*cwd;

	cwd = getpwd(data);
	if (!cwd[0])
	{
		free(cwd);
		return (0);
	}
	i = 0;
	dir = opendir(cwd);
	free(cwd);
	info_dir = readdir(dir);
	while (info_dir)
	{
		if (info_dir->d_name[0] != '.' || hide == '.')
			i++;
		info_dir = readdir(dir);
	}
	closedir(dir);
	return (i);
}

char	**recover_current_repository(t_data *data, char hide)
{
	int				i;
	char			**str;
	struct dirent	*info_dir;
	DIR				*dir;
	int				nb;

	nb = nb_files(data, hide);
	str = ft_calloc(nb + 1, sizeof(char *));
	check_alloc(data, str);
	if (nb == 0)
		return (str);
	dir = opendir(".");
	i = 0;
	info_dir = readdir(dir);
	while (info_dir)
	{
		if (info_dir->d_name[0] != '.' || hide == '.')
		{
			str[i] = ft_strdup(info_dir->d_name);
			check_alloc(data, str[i]);
			i++;
		}
		info_dir = readdir(dir);
	}
	closedir(dir);
	return (str);
}

int	len_wilcard(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '*')
		len++;
	return (len);
}

void	join_wildcard(t_data *data, char **s, char **wildcard)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (wildcard[i])
	{
		str = ft_strjoinfree(str, wildcard[i++], 1);
		check_alloc(data, str);
		if (wildcard[i])
			str = ft_strjoinfree(str, " ", 1);
	}
	free(*s);
	ft_free_2d_char_null_ended(wildcard);
	*s = str;
}

int	handle_wildcard_files(t_data *data, t_token *token)
{
	char	*s;
	t_list	*current;
	t_redir	*redir;
	char	**expand_wildcard;

	if (!token->command->redirections)
		return (EXIT_IGNORE);
	current = token->command->redirections;
	while (current)
	{
		redir = (t_redir *) current->content;
		s = ft_strdup(redir->string);
		check_alloc(data, s);
		expand_wildcard = ft_expand_wildcard(data, s);
		join_wildcard(data, &s, expand_wildcard);
		if (!ft_isemptystr(s))
		{
			free(redir->string);
			redir->string = s;
		}
		else
			free(s);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
