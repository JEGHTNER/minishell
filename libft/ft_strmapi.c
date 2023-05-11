/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:30:59 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 11:09:56 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*temp;
	int		s_len;
	int		ind;

	ind = 0;
	s_len = ft_strlen((char *)s);
	temp = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!temp)
		return (0);
	while (s_len)
	{
		temp[ind] = f(ind, s[ind]);
		ind++;
		s_len--;
	}
	temp[ind] = '\0';
	return (temp);
}
