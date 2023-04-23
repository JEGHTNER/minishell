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
#include <stdio.h>

void	put_in_tree(t_cmd *cmd, t_token *to_put)
{
	t_token *cur;
	t_token	*tmp;

	cur = cmd->tree_head;
	if (cmd->tree_head == 0)
	{
		cmd->tree_head = to_put;
		if (cmd->tree_head->type == PIPE)
			cmd->tree_head->right = to_put;
		return ;
	}
	else
	{
		if (cur->type == PIPE)
		{
			while (cur->right != 0)
				cur = cur->right;
			if (cur->left == 0)
				cur->left = to_put;
			else if (cur->right == 0)
				cur->right = to_put;
		}
		else if (cur->type == CMD)
		{
			tmp = cur;
			cmd->tree_head = to_put;
			cmd->tree_head->left = tmp;
		}
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
		while (idx < to_put->argc)
		{
			cur = cur->next;
			idx++;
		}
	}
}
