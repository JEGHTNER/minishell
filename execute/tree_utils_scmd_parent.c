/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_scmd_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 04:52:34 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/14 23:12:47 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_pipe(t_token *node)
{
	close(node->pipe_fd[WRITE]);
	dup2(node->pipe_fd[READ], STDIN_FILENO);
	close(node->pipe_fd[READ]);
}

void	parent_process(t_token *node, t_cmd *cmd, int is_builtin, int pid)
{
	if (node->pipe_fd && node->last_flag == 0)
		parent_pipe(node);
	else
		parent_redir_last(node, cmd, is_builtin);
	if (node->last_flag == 1 || !node->pipe_fd)
		parent_wait(node, is_builtin, pid);
}

void	parent_wait(t_token *node, int is_builtin, int pid)
{
	int	status;

	if (node->pipe_fd || !is_builtin)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_exit_status = WTERMSIG(status) + 128;
	}
	while (wait(NULL) > 0)
		;
}

void	parent_redir_last(t_token *node, t_cmd *cmd, int is_builtin)
{
	if (*node->redirect_flag && !*node->fail_flag && !node->pipe_fd)
		if (is_builtin)
			do_builtin(is_builtin, node, cmd);
	dup2(cmd->back_up_fd[READ], STDIN_FILENO);
	dup2(cmd->back_up_fd[WRITE], STDOUT_FILENO);
	if (is_builtin && !*node->redirect_flag && !*node->fail_flag \
	&& !node->pipe_fd)
		do_builtin(is_builtin, node, cmd);
}
