/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:38:48 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/26 18:38:50 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_token	*init_token(void)
{
	t_token	*to_ret;

	to_ret = (t_token *)malloc(sizeof(t_token));
	if (!to_ret)
		ft_exit_with_error("malloc error", 0);
	to_ret->argv = 0;
	to_ret->argc = 0;
	to_ret->is_env = NO;
	to_ret->is_pipe = NO;
	to_ret->cmd_path = 0;
	to_ret->left = 0;
	to_ret->right = 0;
	return (to_ret);
}

void	insert_cmd(t_token **head, t_token *to_put)
{
	t_token	*tmp;
	t_token	*cur;
	t_token	*pipe;

	cur = *head;
	tmp = init_token();
	if (!tmp)
		ft_exit_with_error("malloc error", 0);
	tmp->cat = CMD;
	tmp->right = to_put;
	if ((*head) == (t_token *)0)
		*head = tmp;
	else
	{
		pipe = init_token();
		if (!pipe)
			ft_exit_with_error("malloc error", 0);
		pipe->cat = PIPE;
		pipe->left = tmp;
		while (cur->right)
			cur = cur->right;
		cur->right = pipe;
	}
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
	t_token	*tmp;

	cur = (*head);
	tmp = init_token();
	if (!tmp)
		ft_exit_with_error("malloc error", 0);
	tmp->cat = REDIRS;
	tmp->left = to_put;
	if (cur->cat == PIPE)
	{
		while (cur->right)
			cur = cur->right;
		cur = cur->left;
	}
	if (cur->left == 0)
		cur->left = tmp;
	else
	{
		cur = cur->left;
		while (cur->right)
			cur = cur->right;
		cur->right = tmp;
	}
}
