/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:26:57 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_pink(char *msg)
{
	ft_printf("%s%s%s", P_PINK, msg, P_NOC);
}

void	ft_put_green(char *msg)
{
	ft_printf("%s%s%s", P_GREEN, msg, P_NOC);
}

void	ft_put_yellow(char *msg)
{
	ft_printf("%s%s%s", P_YELLOW, msg, P_NOC);
}
