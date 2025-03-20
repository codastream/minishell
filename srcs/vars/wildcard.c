#include "../../includes/shell.h"

char  *define_wildcard(char *s, int i)
{
	int	len;

	len = 0;
	while(i > 0 && s[i - 1] != ' ')
		i--;
	while (s[i + len] && s[i + len] != ' ')
		len++;
	return (strndup(&s[i], len));
}

int	next_wildcard(char *s, char **wildcard)
{
	int	i = 0;

	while (s[i])
	{
		if (s[i] == '*')
		{
			*wildcard = define_wildcard(s, i);
			i++;
			return (1);
		}
		i++;
	}
	return (0);
}

int	nb_files(char hide)
{
	int	i;
	struct dirent *info_dir;
	DIR *dir;

	i = 0;
	dir = opendir(".");
	while ((info_dir = readdir(dir)))
	{
		if (info_dir->d_name[0] != '.' || hide == '.')
			i++;
	}
	closedir(dir);
	return (i);
}

char  **recover_current_repository(char hide)
{
	int	i;
	char  **str;
	struct dirent *info_dir;
	DIR *dir;

	str = ft_calloc(nb_files(hide) + 1, sizeof(char *));
	dir = opendir(".");
	i = 0;
	while ((info_dir = readdir(dir)))
	{
		if (info_dir->d_name[0] != '.' || hide == '.')
		{
			str[i] = ft_strdup(info_dir->d_name);
			i++;
		}
	}
	closedir(dir);
	return (str);
}

/*
{
	int	i;
	char **current_repository;
	char *lst[4] = {"test.c", "autre_test", "Atest", "Aautre_.ctest.c"};

	i = 0;
	current_repository = ft_calloc(6, sizeof(char *));
	while(i != 4)
	{
		current_repository[i] = ft_strdup(lst[i]);
		i++;
	}
	return (current_repository);
}*/

int	len_wilcard(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '*')
		len++;
	return (len);
}

int	ft_cmp_wildcard(char *rep, char *wildcard)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("-> %s - %s\n", rep, wildcard);
	while (rep[i])
	{
		if (wildcard[j] == '*')
		{
			while (wildcard[j] == '*')
				j++;
			while (rep[i] && (ft_strncmp(&rep[i], &wildcard[j], len_wilcard(&wildcard[j])) || !wildcard[j]))
				i++;
			if (!rep[i] && wildcard[j])
				return (0);
		}
		else if (rep[i] != wildcard[j])
		{
			if (wildcard[j])
				return (0);
			while (j > 0 && wildcard[j] != '*')
				j--;
			continue;
		}
		i++;
		j++;
	}
	printf("end\n");
	return (1);
}

char  **ft_expand_wildcard(char *str)
{
	int	  i;
	int	  j;
	int	  len;
	char  **wildcard;
	char  **current_repository = NULL;
	
	i = 0;
	j = 0;
	len = 0;
	current_repository = recover_current_repository(str[0]);
	while (current_repository[i])
	{
		if (ft_cmp_wildcard(current_repository[i++], str))
			len++;
	}
	wildcard = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (current_repository[i])
	{
		if (ft_cmp_wildcard(current_repository[i], str))
			wildcard[j++] = ft_strdup(current_repository[i]);
		i++;
	}
	ft_free_2d_char_null_ended(current_repository);
	return (wildcard);
}

void  join_wildcard(char **s, char **wildcard)
{
	int	  i;
	int	  j;
	int	  len;
	char  *str;
	char  *result;

	i = 0;
	str = NULL; 
	while (wildcard[i])
	{
		printf("-> %s\n", wildcard[i]);
		str = ft_strjoinfree(str, wildcard[i++], 1);
		if (wildcard[i])
			str = ft_strjoinfree(str, " ", 1);
	}
	i = 0;
	len = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '*')
		{
			while (i > 0 && (*s)[i - 1] != ' ')
				i--;
			while ((*s)[i + len] && (*s)[i + len] != ' ')
				len++;
			result = ft_calloc(ft_strlen(*s) - len + ft_strlen(str) + 1, 1);
			break ;
		}
		i++;
	}
	j = 0;
	while (j != i)
	{
		result[j] = (*s)[j];
		j++;
	}
	while (j != i + (int)ft_strlen(str))
	{
		result[j] = str[j - i];
		j++;
	}
	while ((*s)[i + len])
		result[j++] = (*s)[len + i++];
	free(*s);
	free(str);
	ft_free_2d_char_null_ended(wildcard);
	*s = result;
}

int	handle_wilcard(t_data *data, t_token **tokens, t_token *token)
{
	char  *s;
	char  *wildcard;
	char  **expand_wildcard;

	s = token->string;
	(void)tokens;
	(void)data;
	while (next_wildcard(s, &wildcard))
	{
		expand_wildcard = ft_expand_wildcard(wildcard);
		free(wildcard);
		join_wildcard(&s, expand_wildcard);
	}
	token->string = s;
	return(0);
}

/*
int	main(int ac, char **av)
{
	handle_wilcard(strdup(av[1]));
	return(0);
}*/
