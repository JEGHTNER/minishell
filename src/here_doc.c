/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:10:22 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/30 17:24:05 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/lib/include/pipex_bonus.h"
#include "inc/minishell_jehelee.h"

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
	while (1)
	{
		ft_putstr_fd("here_doc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	free(file_name);
}

void	here_doc(char *limiter, t_token *node)
{
	int		fd;
	char	*file_name;
	char	*tmp;

	// here_doc_tmp(limiter, node->hd_index);
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

int	is_here_doc(t_pipex *pipex, char *argv_i)
{
	if (ft_strncmp(argv_i, "here_doc", 8) == 0 && ft_strlen(argv_i) == 8)
	{
		pipex->here_doc_flag = 1;
		return (1);
	}
	return (0);
}
