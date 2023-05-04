/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:20:19 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/14 14:01:15 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new || !lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		new->next = 0;
		return ;
	}
	temp = *lst;
	while ((*lst)->next != 0)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
	(*lst) = temp;
}
