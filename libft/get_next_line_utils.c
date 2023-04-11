/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:25:26 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/26 12:25:31 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return (0);
}

char	*ft_substr_gnl(char const *s, unsigned int start, unsigned int end)
{
	char	*temp;
	size_t	ind;
	size_t	mal_size;

	ind = 0;
	if (!s)
		return (0);
	if (start >= (unsigned int)ft_strlen_gnl((char *)s))
		mal_size = 1;
	else if (end + 1 >= ft_strlen_gnl((char *)s))
		mal_size = ft_strlen_gnl((char *)s) - start + 1;
	else
		mal_size = end - start + 2;
	temp = (char *)malloc(sizeof(char) * mal_size);
	if (!temp)
		return (0);
	if ((ft_strlen_gnl((char *)s) > (size_t)(start)))
	{
		while (start <= end && s[start])
			temp[ind++] = s[start++];
	}
	temp[ind] = '\0';
	return (temp);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*temp;
	size_t	src_len;
	size_t	ind;

	src_len = ft_strlen_gnl(s1);
	ind = 0;
	temp = (char *)malloc((src_len + 1) * sizeof(char));
	if (!temp)
		return (0);
	while (*(s1 + ind))
	{
		*(temp + ind) = *(s1 + ind);
		ind++;
	}
	*(temp + ind) = '\0';
	return (temp);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	ind;
	char	*temp;

	if (!s1)
		return (ft_strdup_gnl(s2));
	s1_len = ft_strlen_gnl((char *)s1);
	s2_len = ft_strlen_gnl((char *)s2);
	ind = 0;
	temp = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!temp)
		return (0);
	while (s1[ind])
	{
		temp[ind] = s1[ind];
		ind++;
	}
	while (*s2)
		temp[ind++] = *s2++;
	temp[ind] = '\0';
	return (temp);
}
