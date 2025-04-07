/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:49:56 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/29 19:08:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;
	t_list	*mapped_elem;

	if (!lst || !f || !del)
		return (NULL);
	mapped = ft_lstnew(f(lst->content));
	if (!mapped)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		mapped_elem = ft_lstnew(f(lst->content));
		if (!mapped_elem)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		ft_lstadd_back(&mapped, mapped_elem);
		lst = lst->next;
	}
	return (mapped);
}
