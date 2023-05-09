/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:23:11 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:07 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_mini(t_element **lst, t_element *new)
{
	t_element	*temp;

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

t_element	*ft_lstnew_mini(char *content)
{
	t_element	*temp;

	temp = (t_element *)malloc(sizeof(t_element));
	if (!temp)
		return (0);
	temp->content = content;
	temp->next = 0;
	return (temp);
}
