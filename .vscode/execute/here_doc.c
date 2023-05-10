/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:10:22 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/10 21:20:46 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_read_line(char *limiter, int fd)
{
	char	*line;
	int		pid;
	int		status;

	signal_init(0, 0);
	pid = fork();
	if (pid == 0)
	{
		signal_init_heredoc(1, 1);
		while (1)
		{
			ft_putstr_fd("> ", STDOUT_FILENO);
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, fd);
			free(line);
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status) + 128;
	printf("%d\n", g_exit_status);
}

void	here_doc_tmp(char *limiter, int index)
{
	int		fd;
	char	*line;
	char	*file_name;
	char	*tmp;

	tmp = ft_itoa(index);
	file_name = ft_strjoin("./tmp/tmp_hd", tmp);
	free(tmp);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror(file_name);
	hd_read_line(limiter, fd);
	close(fd);
	free(file_name);
}

void	here_doc(t_token *node)
{
	int		fd;
	char	*file_name;
	char	*tmp;

	tmp = ft_itoa(node->hd_index);
	file_name = ft_strjoin("./tmp/tmp_hd", tmp);
	free(tmp);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		unlink(file_name);
		perror(file_name);
	}
	dup2(fd, STDIN_FILENO);
	if (*node->is_hd && node->pipe_fd && node->last_flag == 0)
	{
		dup2(node->pipe_fd[WRITE], STDOUT_FILENO);
	}
	close(fd);
	free(file_name);
}
