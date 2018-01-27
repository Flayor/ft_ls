/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:50:08 by bnoufel           #+#    #+#             */
/*   Updated: 2017/12/30 17:05:06 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem))
{
	t_list		*begin_list;
	t_list		*temp;
	t_list		*new_list;

	temp = f(lst);
	if (!lst || !f)
		return (NULL);
	if (!(new_list = ft_lstnew(temp->content, temp->content_size)))
		return (NULL);
	begin_list = new_list;
	lst = lst->next;
	while (lst)
	{
		temp = f(lst);
		if (!(new_list->next = ft_lstnew(temp->content, temp->content_size)))
			return (NULL);
		new_list = new_list->next;
		lst = lst->next;
	}
	return (begin_list);
}
