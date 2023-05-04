/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:40:17 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/12 15:40:42 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

t_gnllist	*find_fd(t_gnllist **head, int fd)
{
	t_gnllist	*tmp;

	if (!(*head))
	{
		*head = add_fd(fd);
		if (!*head)
			return (NULL);
	}
	tmp = *head;
	while (tmp)
	{
		if (tmp->file_descriptor == fd)
			return (tmp);
		if (tmp->next == NULL)
		{
			tmp->next = add_fd(fd);
			if (!(tmp->next))
				return (NULL);
			tmp->next->prev = tmp;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*remove_fd(t_gnllist *current_fd, t_gnllist **head)
{
	if (!current_fd || !*head)
		return (NULL);
	if (current_fd->prev)
		current_fd->prev->next = current_fd->next;
	if (current_fd->next)
		current_fd->next->prev = current_fd->prev;
	if (current_fd == *head)
		*head = current_fd->next;
	free (current_fd->backup);
	current_fd->backup = NULL;
	free (current_fd->read_buff);
	current_fd->read_buff = NULL;
	free (current_fd);
	return (NULL);
}

char	*split_line(t_gnllist *current_fd, t_gnllist **head)
{
	char	*line;
	char	*tmp;

	line = NULL;
	if (!(current_fd->backup && *(current_fd->backup)))
		return (remove_fd(current_fd, head));
	tmp = ft_strchr_gnl(current_fd->backup, '\n');
	if (tmp)
	{	
		*tmp = '\0';
		line = ft_strjoin_gnl(current_fd->backup, "\n");
		if (!line)
			return (remove_fd(current_fd, head));
		ft_strlcpy_gnl(current_fd->backup, tmp + 1, ft_strlen_gnl(tmp + 1) + 1);
		return (line);
	}
	else
	{
		line = ft_strjoin_gnl(current_fd->backup, "");
		if (!line)
			return (remove_fd(current_fd, head));
		remove_fd(current_fd, head);
		return (line);
	}
}

char	*read_line(int fd, t_gnllist *cur_fd, t_gnllist **head, ssize_t r_size)
{
	char			*line;
	char			*tmp;

	while (1)
	{
		r_size = read(fd, cur_fd->read_buff, BUFFER_SIZE);
		if (r_size == 0)
		{
			line = split_line(cur_fd, head);
			return (line);
		}
		if (r_size == -1)
			return (remove_fd(cur_fd, head));
		cur_fd->read_buff[r_size] = '\0';
		tmp = ft_strjoin_gnl(cur_fd->backup, cur_fd->read_buff);
		if (!tmp)
			return (remove_fd(cur_fd, head));
		free(cur_fd->backup);
		cur_fd->backup = tmp;
		if (ft_strchr_gnl(cur_fd->backup, '\n') != NULL)
		{
			line = split_line(cur_fd, head);
			return (line);
		}
	}
}

char	*get_next_line(int fd)
{
	static t_gnllist	*head;
	t_gnllist			*current_fd;
	char				*line;
	ssize_t				read_size;

	line = NULL;
	read_size = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	current_fd = find_fd(&head, fd);
	if (!current_fd)
		return (NULL);
	line = read_line(fd, current_fd, &head, read_size);
	return (line);
}
