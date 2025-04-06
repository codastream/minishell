/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:24:38 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:25:51 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSION_H
# define CONVERSION_H

int					ft_atoi_base(char *nbr, char *base);
int					ft_atoi(const char *nptr);
long				ft_atol(const char *nptr);
long long			ft_atoll(const char *nptr);
unsigned long long	ft_atoull(const char *nptr);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
bool				ft_is_out_of_int_range(char *nb);
char				*ft_itoa(int n);
char				*ft_ltoa(long n);
char				*ft_lutoa_base(unsigned long long n, char *base);
bool				is_valid_number_for_base(char *nbr, char *base);
bool				is_valid_base(char *base);
bool				is_atoi_str(char *str);
bool				is_atoll_str(char *str);
int					ft_hextoi(const char *nb);

#endif
