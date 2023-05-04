/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:42:28 by jehelee           #+#    #+#             */
/*   Updated: 2023/02/04 18:19:28 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_gnllist
{
	int					file_descriptor;
	char				*backup;
	char				*read_buff;
	struct s_gnllist	*next;
	struct s_gnllist	*prev;
}t_gnllist;

t_gnllist	*add_fd(int fd);
t_gnllist	*find_fd(t_gnllist **head, int fd);
char		*get_next_line(int fd);
size_t		ft_strlcpy_gnl(char *dst, const char *src, size_t size);
size_t		ft_strlen_gnl(const char *string);
char		*ft_strjoin_gnl(char const *string1, char const *string2);
char		*ft_strchr_gnl(const char *string, int c);
char		*remove_fd(t_gnllist *current_fd, t_gnllist **head);
char		*split_line(t_gnllist *current_fd, t_gnllist **head);
char		*read_line(int fd, t_gnllist *c_fd, t_gnllist **h, ssize_t r_size);

#endif