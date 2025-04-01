#include "shell.h"

int	nb_files(char hide)
{
	int				i;
	struct dirent	*info_dir;
	DIR				*dir;

	i = 0;
	dir = opendir(".");
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

char	**recover_current_repository(char hide)
{
	int				i;
	char			**str;
	struct dirent	*info_dir;
	DIR				*dir;

	str = ft_calloc(nb_files(hide) + 1, sizeof(char *));
	dir = opendir(".");
	i = 0;
	info_dir = readdir(dir);
	while (info_dir)
	{
		if (info_dir->d_name[0] != '.' || hide == '.')
		{
			str[i] = ft_strdup(info_dir->d_name);
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

void	join_wildcard(char **s, char **wildcard)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (wildcard[i])
	{
		str = ft_strjoinfree(str, wildcard[i++], 1);
		if (wildcard[i])
			str = ft_strjoinfree(str, " ", 1);
	}
	free(*s);
	ft_free_2d_char_null_ended(wildcard);
	*s = str;
}
