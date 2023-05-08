/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 04:49:21 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/08 21:44:40 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redir_case_dr(t_token *node)
{
	int	fd;

	*(node->redirect_flag) = 1;
	if (*node->fail_flag)
		return ;
	fd = open(node->argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	exec_redir_case_r(t_token *node)
{
	int	fd;

	*(node->redirect_flag) = 1;
	if (*node->fail_flag)
		return ;
	fd = open(node->argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	exec_redir_case_l(t_token *node)
{
	int	fd;

	*(node->redirect_flag) = 1;
	fd = open(node->argv[1], O_RDONLY);
	if (fd < 0)
	{
		*node->fail_flag = 1;
		dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
		ft_putstr_fd("minishell: ", 2);
		perror(node->argv[1]);
		g_exit_status = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
