/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 07:58:05 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/14 14:17:20 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_mall_size(char *s, unsigned int start, size_t len)
{
	if (start >= (unsigned int)ft_strlen((char *)s))
		return (1);
	else if (len >= ft_strlen((char *)s) - start)
		return (ft_strlen((char *)s) - start + 1);
	else
		return (len + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	ind;

	ind = 0;
	temp = (char *)malloc(sizeof(char) * ft_mall_size((char *)s, start, len));
	if (!temp)
		return (0);
	if ((ft_strlen((char *)s) > (size_t)(start)))
	{
		while (s[start] && len > 0)
		{
			temp[ind] = s[start];
			ind++;
			start++;
			len--;
		}
	}
	temp[ind] = '\0';
	return (temp);
}
