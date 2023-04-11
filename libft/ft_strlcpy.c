/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:53:35 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 11:03:21 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	ind;
	size_t	src_len;

	ind = 0;
	src_len = ft_strlen((char *)src);
	if (!dst || !src)
		return (0);
	while ((ind < src_len) && (ind + 1 < dstsize))
	{
		((char *)dst)[ind] = src[ind];
		ind++;
	}
	if (dstsize > 0)
		((char *)dst)[ind] = '\0';
	return (src_len);
}
