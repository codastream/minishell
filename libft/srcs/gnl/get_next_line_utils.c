/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:22:23 by fpetit            #+#    #+#             */
/*   Updated: 2024/11/27 13:13:59 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_nullok(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin_free_first(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined;
	size_t	i;

	s1_len = ft_strlen_nullok(s1);
	s2_len = ft_strlen_nullok(s2);
	joined = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		joined[i] = s1[i];
		i++;
	}
	while (i < (s1_len + s2_len))
		joined[i++] = *s2++;
	joined[i] = '\0';
	free(s1);
	return (joined);
}

char	*get_extra(char *str)
{
	unsigned int	i;
	size_t			len;
	char			*extra;

	i = 0;
	len = ft_strlen_nullok(str);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if ((i + 1 >= len) || (str[i] == '\n' && str[i + 1] == '\0'))
		extra = NULL;
	else
		extra = ft_substr_gnl(str, i + 1, len);
	return (extra);
}

char	*trim_line(char *str)
{
	unsigned int	i;
	char			*trimmed;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		trimmed = ft_substr_gnl(str, 0, i);
	else
		trimmed = ft_substr_gnl(str, 0, i + 1);
	free(str);
	return (trimmed);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			s_len;
	unsigned int	sub_len;
	char			*subbed;

	if (!s)
		return (NULL);
	s_len = ft_strlen_nullok((char *)s);
	if (start + len < s_len)
		sub_len = len;
	else
		sub_len = s_len - start;
	subbed = malloc((sub_len + 1) * sizeof(char));
	i = 0;
	while (i < sub_len)
	{
		subbed[i] = s[start + i];
		i++;
	}
	subbed[i] = '\0';
	return (subbed);
}
