/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:15:09 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/05 19:12:39 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(t_cmd *cmd, t_env_lst *find)
{
	if (find == NULL)
		return ;
	if (find == cmd->env_head)
	{
		cmd->env_head = find->next;
		free(find->key);
		free(find->value);
		free(find);
		return ;
	}
	find->prev->next = find->next;
	if (find->next)
		find->next->prev = find->prev;
	free(find->key);
	free(find->value);
	free(find);
	return ;
}
