/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:24:06 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:24:52 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# define PRINTF_ERROR -1

int					ft_print_address(intptr_t address);
void				ft_print_array_int(int *tab, int size);
void				ft_print_tabstr(char **tab);
int					ft_print_char(int c);
int					ft_print_hexa(unsigned long long n, int is_upper);
int					ft_print_integer(int n);
int					ft_print_str(const char *s);
int					ft_print_unsigned(unsigned int n);
int					ft_printf(const char *s, ...);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_puterr(char *s);
void				ft_put_pink(char *msg);
void				ft_put_green(char *msg);
void				ft_put_yellow(char *msg);

int					ft_print_address_fd(int fd, intptr_t address);
int					ft_print_char_fd(int fd, int c);
int					ft_print_hexa_fd(int fd, unsigned long long n, \
						int is_upper);
int					ft_print_integer_fd(int fd, int n);
int					ft_print_str_fd(int fd, const char *s);
int					ft_print_unsigned_fd(int fd, unsigned int n);
int					ft_printfd(int fd, const char *s, ...);

#endif
