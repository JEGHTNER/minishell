/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:38:48 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/14 23:13:47 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(t_cat type)
{
	t_token	*to_ret;

	to_ret = (t_token *)malloc(sizeof(t_token));
	if (!to_ret)
		ft_exit_with_error("malloc error\n", 0);
	to_ret->argv = 0;
	to_ret->argc = 0;
	to_ret->cat = type;
	to_ret->is_env = NO;
	to_ret->is_pipe = NO;
	to_ret->pipe_fd = NULL;
	to_ret->cmd_path = 0;
	to_ret->left = 0;
	to_ret->right = 0;
	to_ret->last_flag = 0;
	to_ret->hd_index = 0;
	to_ret->is_hd = 0;
	return (to_ret);
}

void	insert_cmd(t_token **head, t_token *to_put)
{
	t_token	*tmp;
	t_token	*cur;

	cur = *head;
	tmp = init_token(CMD);
	tmp->right = to_put;
	if ((*head) == (t_token *)0)
		*head = tmp;
	else if (cur->cat == CMD)
	{
		free(cur->right);
		free(tmp);
		cur->right = to_put;
	}
	else
		insert_cmd_when_head_pipe(cur, tmp, to_put);
}

void	insert_pipe(t_token **head, t_token *to_put)
{
	t_token	*cur;

	cur = (*head);
	if (cur->cat == CMD)
	{
		to_put->left = cur;
		(*head) = to_put;
	}
	else
	{
		while (cur->right)
			cur = cur->right;
		cur->right = to_put;
	}
}

void	insert_redir(t_token **head, t_token *to_put)
{
	t_token	*cur;
	t_token	*tmp_head;

	cur = (*head);
	tmp_head = (*head);
	if ((*head) == (t_token *)0)
		*head = init_redir_token(to_put, 0);
	else if (cur->cat == CMD)
	{
		div_redir_token(cur, to_put);
		*head = tmp_head;
	}
	else
		insert_redir_when_head_pipe(cur, to_put);
}
