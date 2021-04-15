/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:28:45 by adenhez           #+#    #+#             */
/*   Updated: 2020/11/19 20:53:29 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*li;
	t_list	*temp;

	if (lst == NULL || f == NULL)
		return (NULL);
	li = ft_lstnew(f(lst->content));
	if (li == NULL)
	{
		ft_lstclear(&li, del);
		return (NULL);
	}
	lst = lst->next;
	while (lst)
	{
		if (!(temp = ft_lstnew(f(lst->content))))
			ft_lstclear(&temp, del);
		ft_lstadd_back(&li, temp);
		lst = lst->next;
	}
	return (li);
}
