/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:24:52 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/26 15:39:56 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*read_temp(int fd, char *temp)
{
	ssize_t	size;
	char	*buff;
	char	*tmp;

	size = 42;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	while (size && ft_strchr_gnl(temp, '\n') == 0)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size < 0)
		{
			free(buff);
			free(temp);
			return (0);
		}
		buff[size] = '\0';
		tmp = ft_strjoin_gnl(temp, buff);
		free(temp);
		temp = tmp;
	}
	free(buff);
	return (temp);
}

static char	*put_line(char *temp)
{
	size_t	ind;
	char	*to_put;

	ind = 0;
	if (!temp)
		return (0);
	if (!(temp[ind]))
		return (0);
	while (temp[ind] && temp[ind] != '\n')
		ind++;
	to_put = ft_substr_gnl(temp, 0, ind);
	if (!to_put)
		return (0);
	return (to_put);
}

static char	*refresh_temp(char *temp)
{
	size_t	ind;
	size_t	end_ind;
	char	*to_refresh;

	ind = 0;
	end_ind = 0;
	while (temp[ind] && temp[ind] != '\n')
		ind++;
	while (temp[end_ind])
		end_ind++;
	if (ind == end_ind)
	{
		free(temp);
		return (0);
	}
	to_refresh = ft_substr_gnl(temp, ind + 1, end_ind);
	free(temp);
	return (to_refresh);
}

char	*get_next_line(int fd)
{
	static char	*temp[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	temp[fd] = read_temp(fd, temp[fd]);
	if (!temp[fd])
		return (0);
	line = put_line(temp[fd]);
	temp[fd] = refresh_temp(temp[fd]);
	return (line);
}
