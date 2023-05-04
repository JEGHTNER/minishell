/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:23:37 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:17:04 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_node;
	t_list	*new_head;
	void	*ptr;

	if (!lst || !f || !del)
		return (0);
	tmp = lst;
	new_head = 0;
	while (tmp)
	{
		ptr = f(tmp -> content);
		new_node = ft_lstnew(ptr);
		if (!(new_node))
		{
			ft_lstclear(&new_head, del);
			del(ptr);
			return (0);
		}
		ft_lstadd_back(&new_head, new_node);
		tmp = tmp->next;
	}
	return (new_head);
}
