/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:47:28 by jmassavi          #+#    #+#             */
/*   Updated: 2025/04/02 17:58:38 by fpetit           ###   ########.fr       */
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

char	**recover_current_repository(t_data *data, char hide, char *s)
{
	int				i;
	char			**strs;
	struct dirent	*info_dir;
	DIR				*dir;
	int				nb;

	strs = init_strs(data, hide, s, &nb);
	if (nb == 0)
		return (strs);
	dir = opendir(".");
	i = 0;
	info_dir = readdir(dir);
	while (info_dir)
	{
		if (info_dir->d_name[0] != '.' || hide == '.')
		{
			strs[i] = ft_strdup(info_dir->d_name);
			if (!strs[i])
				handle_failedadd(data, strs, s, dir);
			i++;
		}
		info_dir = readdir(dir);
	}
	closedir(dir);
	return (strs);
}

int	len_wilcard(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '*')
		len++;
	return (len);
}

int	adjust_file(t_data *data, t_redir *redir, char **expanded)
{
	if (!expanded)
		return (EXIT_IGNORE);
	if (expanded[0] && expanded[1])
	{
		ft_free_2d_char_null_ended(expanded);
		printerr_source(redir->string, "ambiguous redirect");
		update_last_return(data, EXIT_FAILURE);
		free_after_exec(data);
		return (EXIT_FAILURE);
	}
	free(redir->string);
	redir->string = expanded[0];
	free(expanded);
	return (EXIT_SUCCESS);
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
		free(s);
		if (adjust_file(data, redir, expand_wildcard))
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
