/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:38:21 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/05 17:01:34 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	red_args = node->argv;
	if (ft_strlen(red_args[0]) == 2 && !ft_strncmp(red_args[0], "<<", 2))
	{
		here_doc(node);
		*(node->is_hd) = 1;
	}
	else if (ft_strlen(red_args[0]) == 2 && !ft_strncmp(red_args[0], ">>", 2))
	{
		*(node->redirect_flag) = 1;
		if (*node->fail_flag)
			return (1);
		fd = open(red_args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (ft_strlen(red_args[0]) == 1 && !ft_strncmp(red_args[0], ">", ft_strlen(red_args[0])))
	{
		*(node->redirect_flag) = 1;
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

int	exec_cmd(t_token *node)
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

int	check_builtin(char *str)
{
	if (ft_strlen(str) == 4 && !ft_strncmp(str, "echo", 4))
		return (ECH);
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, "cd", 2))
		return (CD);
	else if (ft_strlen(str) == 3 && !ft_strncmp(str, "pwd", 3))
		return (PWD);
	else if (ft_strlen(str) == 6 && !ft_strncmp(str, "export", 6))
		return (EXPORT);
	else if (ft_strlen(str) == 5 && !ft_strncmp(str, "unset", 5))
		return (UNSET);
	else if (ft_strlen(str) == 3 && !ft_strncmp(str, "env", 3))
		return (ENV);
	else if (ft_strlen(str) == 4 && !ft_strncmp(str, "exit", 4))
		return (EXIT);
	return (NOT);
}

// int	do_builtin(int is_builtin, t_token *node, t_list **my_env)
// {
// 	if (is_builtin == ECH)
// 	{
// 		echo(node->argv);
// 		return (exit_status);
// 	}
// 	else if (is_builtin == CD)
// 	{
// 		cd(my_env, node->argv);
// 		return (exit_status);
// 	}
// 	else if (is_builtin == PWD)
// 	{
// 		pwd();
// 		return (exit_status);
// 	}
// 	else if (is_builtin == EXPORT)
// 	{
// 		export(my_env, node->argv);
// 		return (exit_status);
// 	}
// 	else if (is_builtin == UNSET)
// 	{
// 		unset(my_env, node->argv);
// 		return (exit_status);
// 	}
// 	else if (is_builtin == ENV)
// 	{
// 		env(my_env);
// 		return (exit_status);
// 	}
// 	else if (is_builtin == EXIT)
// 	{
// 		ft_exit(node->argv);
// 		printf("exit\n");
// 		exit (exit_status);
// 	}
// }

int	do_builtin(int is_builtin, t_token *node, t_cmd *cmd)
{
	if (is_builtin == ECH)
	{
		echo(node->argv);
		return (exit_status);
	}
	else if (is_builtin == CD)
	{
		cd(cmd, node->argv);
		return (exit_status);
	}
	else if (is_builtin == PWD)
	{
		pwd();
		return (exit_status);
	}
	else if (is_builtin == EXPORT)
	{
		export(cmd, node->argv);
		return (exit_status);
	}
	else if (is_builtin == UNSET)
	{
		unset(cmd, node->argv);
		return (exit_status);
	}
	else if (is_builtin == ENV)
	{
		env(cmd);
		return (exit_status);
	}
	else if (is_builtin == EXIT)
	{
		ft_exit(node->argv);
		printf("exit\n");
		exit (exit_status);
	}
}

// int	exec_scmd(t_token *node, t_list **my_env)
// {
// 	char	**env_table;
// 	int		pid;
// 	char	**path_args;
// 	char	*path;
// 	int		is_builtin;

// 	is_builtin = check_builtin(node->argv[0]);
// 	pid = fork();
// 	if (pid < 0)
// 		perror("pipe");
// 	if (pid == 0) // child
// 	{
// 		env_table = lst_to_table(my_env);
// 		path_args = get_path_args(my_env);
// 		path = get_path(node->argv[0], path_args);
// 		if (*node->fail_flag)
// 			exit(1);
// 		if (!path && !is_builtin)
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(node->argv[0], 2);
// 			ft_putstr_fd(": command not found\n", 2);
// 			exit(127);
// 		}
// 		if (*node->redirect_flag)
// 		{
// 			if (node->pipe_fd)
// 			{
// 				close(node->pipe_fd[WRITE]);
// 				close(node->pipe_fd[READ]);
// 			}
// 			if (!is_builtin)
// 			{
// 				if (execve(path, node->argv, env_table) < 0)
// 				{
// 					perror("execve");
// 					exit(127);
// 				}
// 			}
// 			else
// 				exit(do_builtin(is_builtin, node, my_env));
// 		}
// 		if (node->pipe_fd && node->last_flag == 0)
// 		{
// 			close(node->pipe_fd[READ]);
// 			dup2(node->pipe_fd[WRITE], STDOUT_FILENO);
// 			close(node->pipe_fd[WRITE]);
// 			if (!is_builtin)
// 			{
// 				if (execve(path, node->argv, env_table) < 0)
// 				{
// 					perror("execve");
// 					exit(127);
// 				}
// 			}
// 			else
// 				exit(do_builtin(is_builtin, node, my_env));
// 		}
// 		dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
// 		if (!is_builtin)
// 		{
// 			if (execve(path, node->argv, env_table) < 0)
// 			{
// 				perror("execve");
// 				exit(127);
// 			}
// 		}
// 		else
// 			exit(0);
// 	}
// 	else // parent
// 	{
// 		int	status;

// 		if (node->pipe_fd && node->last_flag == 0)
// 		{
// 			close(node->pipe_fd[WRITE]);
// 			dup2(node->pipe_fd[READ], STDIN_FILENO);
// 			close(node->pipe_fd[READ]);
// 		}
// 		else
// 		{
// 			if (*node->redirect_flag && !node->pipe_fd)
// 				if (is_builtin)
// 					do_builtin(is_builtin, node, my_env);
// 			dup2(node->back_up_fd[READ], STDIN_FILENO);
// 			dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
// 			close(node->back_up_fd[WRITE]);
// 			close(node->back_up_fd[READ]);
// 			if (is_builtin && !*node->redirect_flag && !node->pipe_fd)
// 				do_builtin(is_builtin, node, my_env);
// 		}
// 		if (node->last_flag == 1 || !node->pipe_fd)
// 		{
// 			if (!is_builtin)
// 			{
// 				waitpid(pid, &status, 0);
// 				if (WIFEXITED(status))
// 					exit_status = WEXITSTATUS(status);
// 			}
// 			while (wait(NULL) > 0)
// 				;
// 			printf("exit_status = %d\n", exit_status);
// 		}
// 	}
// }

int	exec_scmd(t_token *node, t_cmd *cmd)
{
	char	**env_table;
	int		pid;
	char	**path_args;
	char	*path;
	int		is_builtin;

	is_builtin = check_builtin(node->argv[0]);
	pid = fork();
	if (pid < 0)
		perror("pipe");
	if (pid == 0) // child
	{
		env_table = lst_to_table(cmd);
		path_args = get_path_args(cmd);
		path = get_path(node->argv[0], path_args);
		if (*node->fail_flag)
			exit(1);
		if (!path && !is_builtin)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(node->argv[0], 2);
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
			if (!is_builtin)
			{
				if (execve(path, node->argv, env_table) < 0)
				{
					perror("execve");
					exit(127);
				}
			}
			else
				exit(do_builtin(is_builtin, node, cmd));
		}
		if (node->pipe_fd && node->last_flag == 0)
		{
			close(node->pipe_fd[READ]);
			dup2(node->pipe_fd[WRITE], STDOUT_FILENO);
			close(node->pipe_fd[WRITE]);
			if (!is_builtin)
			{
				if (execve(path, node->argv, env_table) < 0)
				{
					perror("execve");
					exit(127);
				}
			}
			else
				exit(do_builtin(is_builtin, node, cmd));
		}
		dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
		if (!is_builtin)
		{
			if (execve(path, node->argv, env_table) < 0)
			{
				perror("execve");
				exit(127);
			}
		}
		else
			exit(0);
	}
	else // parent
	{
		int	status;

		if (node->pipe_fd && node->last_flag == 0)
		{
			close(node->pipe_fd[WRITE]);
			dup2(node->pipe_fd[READ], STDIN_FILENO);
			close(node->pipe_fd[READ]);
		}
		else
		{
			if (*node->redirect_flag && !node->pipe_fd)
				if (is_builtin)
					do_builtin(is_builtin, node, cmd);
			dup2(node->back_up_fd[READ], STDIN_FILENO);
			dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
			close(node->back_up_fd[WRITE]);
			close(node->back_up_fd[READ]);
			if (is_builtin && !*node->redirect_flag && !node->pipe_fd)
				do_builtin(is_builtin, node, cmd);
		}
		if (node->last_flag == 1 || !node->pipe_fd)
		{
			if (!is_builtin)
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					exit_status = WEXITSTATUS(status);
			}
			while (wait(NULL) > 0)
				;
			printf("exit_status = %d\n", exit_status);
		}
	}
}
