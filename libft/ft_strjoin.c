/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:03:46 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 11:02:24 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	ind;
	char	*temp;

	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
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
	{
		temp[ind] = *s2;
		ind++;
		s2++;
	}
	temp[ind] = '\0';
	return (temp);
}
