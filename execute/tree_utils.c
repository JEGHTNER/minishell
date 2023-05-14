/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:38:21 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/14 23:13:58 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redirs(t_token *node)
{
	if (node->left)
	{
		node->left->pipe_fd = node->pipe_fd;
		node->left->last_flag = node->last_flag;
		node->left->redirect_flag = node->redirect_flag;
		node->left->fail_flag = node->fail_flag;
		node->left->is_hd = node->is_hd;
	}
	if (node->right)
	{
		node->right->pipe_fd = node->pipe_fd;
		node->right->last_flag = node->last_flag;
		node->right->redirect_flag = node->redirect_flag;
		node->right->fail_flag = node->fail_flag;
		node->right->is_hd = node->is_hd;
	}
}

void	exec_redir(t_token *node, t_cmd *cmd)
{
	if (ft_strlen(node->argv[0]) == 2 && !ft_strncmp(node->argv[0], "<<", 2))
	{
		here_doc(node);
		*(node->is_hd) = 1;
	}
	else if (ft_strlen(node->argv[0]) == 2 && \
	!ft_strncmp(node->argv[0], ">>", 2))
		exec_redir_case_dr(node);
	else if (ft_strlen(node->argv[0]) == 1 && \
	!ft_strncmp(node->argv[0], ">", ft_strlen(node->argv[0])))
		exec_redir_case_r(node);
	else if (ft_strlen(node->argv[0]) == 1 && \
	!ft_strncmp(node->argv[0], "<", ft_strlen(node->argv[0])))
		exec_redir_case_l(node, cmd);
}

void	exec_pipe(t_token *node)
{
	node->pipe_fd = malloc(sizeof(int *) * 2);
	if (pipe(node->pipe_fd) < 0)
		perror("pipe error");
	if (node->left)
		node->left->pipe_fd = node->pipe_fd;
	if (node->right)
		node->right->pipe_fd = node->pipe_fd;
	if (node->right == NULL)
		node->left->last_flag = 1;
}

void	exec_cmd(t_token *node)
{
	node->redirect_flag = malloc(sizeof(int));
	*(node->redirect_flag) = 0;
	node->fail_flag = malloc(sizeof(int));
	*(node->fail_flag) = 0;
	node->is_hd = malloc(sizeof(int));
	*(node->is_hd) = 0;
	if (node->left)
	{
		node->left->pipe_fd = node->pipe_fd;
		node->left->redirect_flag = node->redirect_flag;
		node->left->fail_flag = node->fail_flag;
		node->left->is_hd = node->is_hd;
	}
	if (node->right)
	{
		node->right->pipe_fd = node->pipe_fd;
		node->right->last_flag = node->last_flag;
		node->right->redirect_flag = node->redirect_flag;
		node->right->fail_flag = node->fail_flag;
		node->right->is_hd = node->is_hd;
	}
}

void	exec_scmd(t_token *node, t_cmd *cmd)
{
	int		pid;
	int		is_builtin;

	if (node->argv && (!ft_strncmp(node->argv[0], "minishell", 9) || \
	!ft_strncmp(node->argv[0], "./minishell", 11)))
		signal_init(0, 0);
	else
		signal_init_default();
	if (!node->argv)
		is_builtin = NOT;
	else
		is_builtin = check_builtin(node->argv[0]);
	pid = fork();
	if (pid < 0)
		perror("pipe");
	if (pid == 0)
		child_process(node, cmd, is_builtin);
	else
		parent_process(node, cmd, is_builtin, pid);
}
