/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:43:06 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 09:43:35 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	size_t	src_len;
	size_t	ind;

	src_len = ft_strlen(s1);
	ind = 0;
	temp = (char *)malloc((src_len + 1) * sizeof(char));
	if (!(temp))
		return (0);
	while (*(s1 + ind))
	{
		*(temp + ind) = *(s1 + ind);
		ind++;
	}
	*(temp + ind) = '\0';
	return (temp);
}
