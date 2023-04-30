/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:38:21 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/30 17:20:52 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell_jehelee.h"

int	exec_redirs(t_token *node)
{
	if (node->left)
	{
		node->left->pipe_fd = node->pipe_fd;
		node->left->last_flag = node->last_flag;
		node->left->redirect_flag = node->redirect_flag;
		node->left->redirect_flag = node->redirect_flag;
		node->left->fail_flag = node->fail_flag;
		node->left->is_hd = node->is_hd;
	}
	if (node->right)
	{
		node->right->pipe_fd = node->pipe_fd;
		node->right->last_flag = node->last_flag;
		node->right->redirect_flag = node->redirect_flag;
		node->right->redirect_flag = node->redirect_flag;
		node->right->fail_flag = node->fail_flag;
		node->right->is_hd = node->is_hd;
	}
}

int	exec_redir(t_token *node)
{
	char 	**red_args;
	int		fd;

	// printf("node->argv[0]: %s\n", node->argv[0]);
	// *(node->redirect_flag) = 1;
	red_args = node->argv;
	if (ft_strlen(red_args[0]) == 2 && !ft_strncmp(red_args[0], "<<", 2))
	{
		here_doc(red_args[1], node);
		*(node->is_hd) = 1;
	}
	else if (ft_strlen(red_args[0]) == 2 && !ft_strncmp(red_args[0], ">>", 2))
	{
		*(node->redirect_flag) = 1;
		// printf("node->fail_flag: %d\n", *node->fail_flag);
		if (*node->fail_flag)
			return (1);
		fd = open(red_args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (ft_strlen(red_args[0]) == 1 && !ft_strncmp(red_args[0], ">", ft_strlen(red_args[0])))
	{
		*(node->redirect_flag) = 1;
		// printf("node->fail_flag: %d\n", *node->fail_flag);
		if (*node->fail_flag)
			return (1);
		fd = open(red_args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (!ft_strncmp(red_args[0], "<", ft_strlen(red_args[0])))
	{
		*(node->redirect_flag) = 1;
		fd = open(red_args[1], O_RDONLY);
		if (fd < 0)
		{
			*node->fail_flag = 1;
			dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
			ft_putstr_fd("minishell: ", 2);
			perror(red_args[1]);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

int	exec_pipe(t_token *node)
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

int exec_cmd(t_token *node)
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

int	exec_scmd(t_token *node, t_list **my_env)
{
	char	**cmd_arr;
	int		i;
	int		pid;
	char	**path_args;
	char	*path;

	pid = fork();
	if (pid < 0)
		perror("pipe");
	if (pid == 0) // child
	{
		char **cmd_args = node->argv;
		path_args = get_path_args(my_env);
		path = get_path(cmd_args[0], path_args);
		// printf("path = %s\n", path);
		if (*node->fail_flag)
			exit(1);
		if (!path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		if (*node->redirect_flag)
		{
			if (node->pipe_fd)
			{
				close(node->pipe_fd[WRITE]);
				close(node->pipe_fd[READ]);
			}
			if (execve(path, cmd_args, my_env) < 0)
			{
				perror("execve");
				exit(127);
			}
		}
		if (node->pipe_fd && node->last_flag == 0)
		{
			close(node->pipe_fd[READ]);
			dup2(node->pipe_fd[WRITE], STDOUT_FILENO);
			close(node->pipe_fd[WRITE]);
			if (execve(path, cmd_args, my_env) < 0)
			{
				perror("execve");
				exit(127);
			}
		}
		dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
		printf("node->lastflag = %d\n", node->last_flag);
		if (execve(path, cmd_args, my_env) < 0)
		{
			perror("execve");
			exit(127);
		}
	}
	else // parent
	{
		wait(NULL);
		if (node->pipe_fd && node->last_flag == 0)
		{
			close(node->pipe_fd[WRITE]);
			dup2(node->pipe_fd[READ], STDIN_FILENO);
			close(node->pipe_fd[READ]);
		}
		else
		{
			dup2(node->back_up_fd[READ], STDIN_FILENO);
			dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
			close(node->back_up_fd[WRITE]);
			close(node->back_up_fd[READ]);
		}
	}
}
