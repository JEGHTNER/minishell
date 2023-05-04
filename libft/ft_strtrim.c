/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:09:48 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/14 15:09:25 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_mall_size_one(int start, int end)
{
	if (start >= end)
		return (1);
	else
		return (end - start + 2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	size_t	start;
	size_t	end;
	size_t	ind;

	start = 0;
	end = ft_strlen((char *)s1);
	while (ft_strlen((char *)s1) > 0 && ft_strrchr(set, s1[start]) != 0)
		start++;
	while (end > 0 && ft_strrchr(set, s1[end]) != 0)
		end--;
	temp = (char *)malloc(sizeof(char) * ft_mall_size_one(start, end));
	if (!temp)
		return (0);
	ind = 0;
	if (*s1)
	{
		while (start <= end)
			temp[ind++] = s1[start++];
	}
	temp[ind] = '\0';
	return (temp);
}
