/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:37:17 by fpetit            #+#    #+#             */
/*   Updated: 2024/11/27 12:2 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>
# include <limits.h>
# include "colors.h"

# include "get_next_line.h"
# include "hash.h"
# include "queue.h"
# include "tab.h"
# include "list.h"
# include "splitter.h"
# include "conversion.h"
# include "string.h"
# include "print.h"

void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_free_2d_char_null_ended(char **tab);
void				ft_free_2d_generic(void **tab, int size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);

bool				ft_is_prime(int n);
bool				ft_is_even(int n);

#endif
