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
	size_t	ind;
	char	*temp;

	if (s1 == 0)
		return (s2);
	if (s2 == 0)
		return ((char *)0);
	ind = 0;
	temp = (char *)malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
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
