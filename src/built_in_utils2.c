/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:15:09 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/16 14:19:06 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"

void	del_env(t_list **my_env, t_list *find)
{
	if (find == NULL)
		return ;
	if (find == *my_env)
	{
		*my_env = find->next;
		if (*my_env)
			(*my_env)->prev = NULL;
		free(find->content);
		free(find);
		return ;
	}
	find->prev->next = find->next;
	if (find->next)
		find->next->prev = find->prev;
	free(find->content);
	free(find);
	return ;
}
