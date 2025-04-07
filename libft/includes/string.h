/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:24:21 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/03 22:17:40 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

typedef struct s_replace
{
	char	*s;
	char	*to_rep;
	char	*replacement;
	int		after_i;
}	t_replace;

bool				ft_isalnum(int c);
int					ft_isalnumstr(char *c);
bool				ft_ischarforenvvar(int c);
bool				ft_isenvvarkeystr(char *s);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
bool				ft_isemptychar(char c);
bool				ft_isemptystr(char *s);
bool				ft_isnumstr(char *s);
bool				ft_is_upper(int c);
int					ft_isprint(int c);
char				**ft_split(char const *s, char c);
char				**ft_split_str(char const *s, char *charset);
char				**split_index(char *s, int index);
char				*ft_strcat(char *dest, char *src);
char				*ft_strchr(const char *s, int c);
int					ft_strchri(const char *s, unsigned char c);
int					ft_strrchri(const char *s, unsigned char c);
int					ft_strcharsi(char *str, char *searchedchars);
int					ft_strstri(char *str, char **searched);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strcmp_igncase(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
char				*ft_strnduup(const char *s, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_multistrjoin(int size, char **strs, char *sep);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strjoinfree(char *s1, char *s2, int value);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little, \
						size_t len);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_tolowerstr(char *s);
char				*ft_subst(char *s, char *to_replace, char *replacement);
char				*ft_subst_first_after_i(char *s, char *to_replace, \
						char *replacement, int after_i);

#endif
