/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:28:21 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/07 20:39:20 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;
	char	*new_string;

	new_string = NULL;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_string = ft_strdup(content);
	new_node -> content = new_string;
	new_node -> index = 0;
	new_node -> next = NULL;
	new_node -> prev = NULL;
	if (!new_string)
		return (NULL);
	return (new_node);
}
