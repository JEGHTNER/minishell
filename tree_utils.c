/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:38:21 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/08 02:08:10 by jehelee          ###   ########.fr       */
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
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	exec_redir(t_token *node)
{
	int		fd;

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
		exec_redir_case_l(node);
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
	else
		return (do_builtin2(is_builtin, node, cmd));
}

int	do_builtin2(int is_builtin, t_token *node, t_cmd *cmd)
{
	if (is_builtin == UNSET)
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
	return (NOT);
}

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
	dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
	if (!is_builtin)
		ft_execute(path, node->argv, env_table);
	else
		exit(0);
}

void	child_process(t_token *node, t_cmd *cmd, int is_builtin)
{
	char	**env_table;
	char	**path_args;
	char	*path;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	env_table = lst_to_table(cmd);
	path_args = get_path_args(cmd);
	path = get_path(node->argv[0], path_args);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
		child_redir(node, is_builtin, cmd);
	if (node->pipe_fd && node->last_flag == 0)
		child_pipe(node, is_builtin, cmd);
	child_last(node, is_builtin, cmd);
}

void	parent_redir_last(t_token *node, t_cmd *cmd, int is_builtin)
{
	if (*node->redirect_flag && !*node->fail_flag && !node->pipe_fd)
		if (is_builtin)
			do_builtin(is_builtin, node, cmd);
	dup2(node->back_up_fd[READ], STDIN_FILENO);
	dup2(node->back_up_fd[WRITE], STDOUT_FILENO);
	close(node->back_up_fd[WRITE]);
	close(node->back_up_fd[READ]);
	if (is_builtin && !*node->redirect_flag && !*node->fail_flag \
	&& (node->last_flag == 1 || !node->pipe_fd))
		do_builtin(is_builtin, node, cmd);
}

void	parent_wait(t_token *node, int is_builtin, int pid)
{
	int	status;

	if (!is_builtin)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			exit_status = WTERMSIG(status) + 128;
	}
	while (wait(NULL) > 0)
		;
}

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

void	exec_scmd(t_token *node, t_cmd *cmd)
{
	int		pid;
	int		is_builtin;

	is_builtin = check_builtin(node->argv[0]);
	pid = fork();
	if (pid < 0)
		perror("pipe");
	if (pid == 0) // child
		child_process(node, cmd, is_builtin);
	else // parent
		parent_process(node, cmd, is_builtin, pid);
}
