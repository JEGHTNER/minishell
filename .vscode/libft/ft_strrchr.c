/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:40:54 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 12:48:59 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	str_len;

	str_len = ft_strlen((char *)s);
	while (str_len)
	{
		if (s[str_len - 1] == (char)c)
			return ((char *)(s + str_len -1));
		str_len--;
	}
	if ((char)c == 0)
		return ((char *)(s + ft_strlen((char *)s)));
	return ((void *) 0);
}
