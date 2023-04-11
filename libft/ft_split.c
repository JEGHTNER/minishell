/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:16:04 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/16 13:20:29 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_word_num_count(char *str, char c)
{
	size_t	temp;
	size_t	ind;

	temp = 0;
	ind = 0;
	while (str[ind])
	{
		if ((str[ind] != c) && (str[ind + 1] == c))
			temp++;
		if ((str[ind] != c) && (str[ind + 1] == '\0'))
			temp++;
		ind++;
	}
	return (temp);
}

static char	**ft_free_wrongone(char *temp, char **total, size_t ind)
{
	free((void *)temp);
	while (ind >= 1)
	{
		free((void *)total[ind - 1]);
		ind--;
	}
	free(total);
	return (0);
}

static char	*ft_put_rightone(char *arr, char *str, char c, size_t *total_i)
{
	size_t	ind;

	ind = 0;
	while (str[*total_i] != c && str[*total_i])
	{
		arr[ind] = str[*total_i];
		ind++;
		(*total_i)++;
	}
	arr[ind] = '\0';
	return (arr);
}

static char	**ft_write_whole(char **total, char *str, char c)
{
	size_t	total_i;
	size_t	ind;
	size_t	tmp_i;

	total_i = 0;
	ind = 0;
	while (str[total_i])
	{
		if (str[total_i] == c)
			total_i++;
		else
		{
			tmp_i = total_i;
			while (str[tmp_i] != c && str[tmp_i])
				tmp_i++;
			total[ind] = (char *)malloc(sizeof(char) * (tmp_i - total_i + 1));
			if (!total[ind])
				return (ft_free_wrongone(total[ind], total, ind));
			else
				total[ind] = ft_put_rightone(total[ind], str, c, &total_i);
			ind++;
		}
	}
	total[ind] = 0;
	return (total);
}

char	**ft_split(char const *s, char c)
{
	char		**total;
	size_t		word_num;

	if (!s)
		return (0);
	word_num = ft_word_num_count((char *)s, c);
	total = (char **)malloc(sizeof(char *) * (word_num + 1));
	if (!total)
		return (0);
	total = ft_write_whole(total, (char *)s, c);
	return (total);
}
