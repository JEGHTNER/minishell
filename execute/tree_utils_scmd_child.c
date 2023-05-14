/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_scmd_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 04:54:33 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/14 23:12:36 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char *path, char **argv, char **env_table)
{
	if (execve(path, argv, env_table) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[0], 2);
		perror(" ");
		exit(127);
	}
}

void	child_redir(t_token *node, int is_builtin, t_cmd *cmd)
{
	char	**env_table;
	char	**path_args;
	char	*path;

	env_table = lst_to_table(cmd);
	path_args = get_path_args(cmd);
	path = get_path(node->argv[0], path_args);
	if (node->pipe_fd)
	{
		close(node->pipe_fd[WRITE]);
		close(node->pipe_fd[READ]);
		if (is_builtin)
			exit(do_builtin(is_builtin, node, cmd));
	}
	if (!is_builtin)
		ft_execute(path, node->argv, env_table);
	else
		exit(0);
}

void	child_pipe(t_token *node, int is_builtin, t_cmd *cmd)
{
	char	**env_table;
	char	**path_args;
	char	*path;

	env_table = lst_to_table(cmd);
	path_args = get_path_args(cmd);
	path = get_path(node->argv[0], path_args);
	close(node->pipe_fd[READ]);
	dup2(node->pipe_fd[WRITE], STDOUT_FILENO);
	close(node->pipe_fd[WRITE]);
	if (!is_builtin)
		ft_execute(path, node->argv, env_table);
	else
		exit(do_builtin(is_builtin, node, cmd));
}

void	child_last(t_token *node, int is_builtin, t_cmd *cmd)
{
	char	**env_table;
	char	**path_args;
	char	*path;

	env_table = lst_to_table(cmd);
	path_args = get_path_args(cmd);
	path = get_path(node->argv[0], path_args);
	dup2(cmd->back_up_fd[WRITE], STDOUT_FILENO);
	if (!is_builtin)
		ft_execute(path, node->argv, env_table);
	else
	{
		if (node->pipe_fd)
			exit(do_builtin(is_builtin, node, cmd));
		else
			exit(0);
	}
}

void	child_process(t_token *node, t_cmd *cmd, int is_builtin)
{
	char			**path_args;
	char			*path;

	signal_init(1, 1);
	if (*node->fail_flag)
		exit(1);
	if (!node->argv)
		exit(g_exit_status);
	path_args = get_path_args(cmd);
	path = get_path(node->argv[0], path_args);
	if (!path && !is_builtin)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (*node->redirect_flag)
		child_redir(node, is_builtin, cmd);
	if (node->pipe_fd && node->last_flag == 0)
		child_pipe(node, is_builtin, cmd);
	child_last(node, is_builtin, cmd);
}
