/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:33:27 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 11:58:10 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	ind;

	dst_len = ft_strlen((char *)dst);
	src_len = ft_strlen((char *)src);
	ind = 0;
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (*(src + ind) && dst_len + 1 + ind < dstsize)
	{
		((char *)dst)[dst_len + ind] = src[ind];
		ind++;
	}
	((char *)dst)[dst_len + ind] = '\0';
	return (dst_len + src_len);
}
