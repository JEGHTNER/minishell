/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:22:56 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/23 12:22:57 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	put_in_tree(t_cmd *cmd, t_token *to_put)
{
	if (cmd->tree_head == 0)
		insert_cmd(&(cmd->tree_head), to_put);
	else
	{
		if (to_put->cat == PIPE)
			insert_pipe(&(cmd->tree_head), to_put);
		else if (to_put->cat == SIMPLE_CMD)
			insert_cmd(&(cmd->tree_head), to_put);
		else
			insert_redir(&(cmd->tree_head), to_put);
	}
}

void	convert_tree(t_cmd *cmd)
{
	size_t		idx;
	t_element   *cur;
	t_token     *to_put;

	cur = cmd->chunk_head;
	while (cur)
	{
		idx = 0;
		to_put = change_element_token(cur);
		put_in_tree(cmd, to_put);
		while (idx < (size_t)to_put->argc)
		{
			cur = cur->next;
			if (!cur)
				break ;
			idx++;
		}
	}
}
