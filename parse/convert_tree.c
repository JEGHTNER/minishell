/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:22:56 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:01 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_in_tree(t_cmd *cmd, t_token *to_put)
{
	if (to_put->cat == PIPE)
		insert_pipe(&(cmd->tree_head), to_put);
	else if (to_put->cat == SIMPLE_CMD)
		insert_cmd(&(cmd->tree_head), to_put);
	else
		insert_redir(&(cmd->tree_head), to_put);
}

void	convert_tree(t_cmd *cmd)
{
	size_t		idx;
	t_element	*cur;
	t_token		*to_put;

	cur = cmd->chunk_head;
	while (cur)
	{
		idx = 0;
		to_put = change_element_token(cur);
		put_in_tree(cmd, to_put);
		while (idx < (size_t)to_put->argc)
		{
			cur = cur->next;
			idx++;
		}
	}
}
