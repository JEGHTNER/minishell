/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:38:48 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:23 by jehelee          ###   ########.fr       */
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
	to_ret->back_up_fd[0] = dup(STDIN_FILENO);
	to_ret->back_up_fd[1] = dup(STDOUT_FILENO);
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
	t_token	*pipe;

	cur = *head;
	tmp = init_token();
	tmp->cat = CMD;
	tmp->right = to_put;
	if ((*head) == (t_token *)0)
		*head = tmp;
	else
	{
		pipe = init_token();
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

t_token	*init_redir_token(t_token *to_put, t_macro flag)
{
	t_token	*to_ret;
	t_token *tmp_redir;
	t_token	*tmp_cmd;

	tmp_redir = init_token();
	tmp_redir->cat = REDIRS;
	tmp_redir->left = to_put;
	if (flag == YES)
	{
		tmp_cmd = init_token();
		tmp_cmd->cat = CMD;
		tmp_cmd->left = tmp_redir;
		return (tmp_cmd);
	}
	else
		return (tmp_redir);
}

void	div_redir_token(t_token **cur, t_token *to_put)
{
	if ((*cur)->left == 0)
		(*cur)->left = init_redir_token(to_put, NO);
	else
	{
		(*cur) = (*cur)->left;
		while ((*cur)->right)
			(*cur) = (*cur)->right;
		(*cur)->right = init_redir_token(to_put, NO);
	}
}

void	insert_redir(t_token **head, t_token *to_put)
{
	t_token	*cur;

	cur = (*head);
	if ((*head) == (t_token *)0)
		*head = init_redir_token(to_put, YES);
	else if (cur->cat == CMD)
		div_redir_token(cur, to_put);
	else
	{
		while (cur->right)
			cur = cur->right;
		if (cur->left)
		{
			cur = cur->left;
			div_redir_token(cur, to_put);
		}
		else
			cur->left = init_redir_token(to_put, YES);
	}
}

// void	insert_redir(t_token **head, t_token *to_put)
// {
// 	t_token	*cur;
// 	t_token	*tmp;
// 	t_token	*tmp_cmd;

// 	cur = (*head);
// 	tmp = init_token();
// 	tmp->cat = REDIRS;
// 	tmp->left = to_put;
// 	if (cur->cat == PIPE)
// 	{
// 		while (cur->right)
// 			cur = cur->right;
// 		cur = cur->left;
// 	}
// 	if (cur->left == 0)
// 		cur->left = tmp;
// 	else
// 	{
// 		cur = cur->left;
// 		while (cur->right)
// 			cur = cur->right;
// 		cur->right = tmp;
// 	}
// }
