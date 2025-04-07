/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:24:25 by fpetit            #+#    #+#             */
/*   Updated: 2025/03/27 14:25:56 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAB_H
# define TAB_H

bool				ft_has_unique_values_array(int *values, int size);
void				ft_quick_sort_tab(int *tab, int from, int to);
int					ft_count_2dchar_null_ended(char **tab);
int					ft_count_3dchar_null_ended(void ***tab);

#endif
