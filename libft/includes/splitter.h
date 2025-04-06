/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:57:27 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:53:26 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLITTER_H
# define SPLITTER_H

# include "libft.h"

typedef struct s_delimiter
{
	char	*opening;
	char	*closing;
	int		level;
	bool	is_closed;
}	t_delimiter;

typedef struct s_splitter
{
	char		*s;
	int			index;
	int			count;
	t_delimiter	**delims;
	char		**seps;
	char		**splitted;
}	t_splitter;

t_splitter	*init_splitter(const char *str, char **seps, \
				t_delimiter **delimiters);
char		**init_splitskipped(t_splitter *splitter, char *s, char **seps, \
				t_delimiter **delims);
void		reset_delim_close_status(t_delimiter **delims);

void		free_delimiters(t_delimiter **delims);
void		free_splitted(char **splitted);
void		free_splitter(t_splitter *splitter);
void		check_malloc(t_splitter *splitter, char **splitted, \
				void *allocated);

t_delimiter	*get_del(char *s, t_delimiter **delims, char delim_type);
int			count_len_till_closing_delim(char *s, t_delimiter *delim);
bool		is_outside_delims(t_delimiter **delims);
bool		can_split_delim(t_delimiter **delims, t_delimiter *delim);

char		*get_sep(char *s, char **seps);
char		*get_sep_not_space(char *s, char **seps);

void		count_word(t_splitter *splitter, size_t *i, int *count);
void		count_sep(char *sep, size_t *i, int *count);
void		go_to_end_of_delim_count(t_splitter *splitter, \
				t_delimiter **delims, size_t *i, int *count);

void		add_sep(t_splitter *splitter, char *sep, size_t *i, \
				char **splitted);
void		add_elem(t_splitter *splitter, char **splitted, int len, size_t *i);
void		go_to_end_of_delim(t_splitter *splitter, char **splitted, \
				size_t *i);
char		**ft_split_skip(const char *str, char **seps, \
				t_delimiter **ignore_delimiters);

#endif
