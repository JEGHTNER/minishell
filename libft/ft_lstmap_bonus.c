/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:22:06 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/14 15:14:42 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*now;
	void	*temp;

	if (!lst || !f || !del)
		return (0);
	head = 0;
	while (lst)
	{
		temp = f(lst->content);
		now = ft_lstnew(temp);
		if (!now)
		{
			free(temp);
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, now);
		lst = lst->next;
	}
	now = 0;
	return (head);
}
