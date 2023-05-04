/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:48:36 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:17:08 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_tmp;
	unsigned char		*src_tmp;

	dst_tmp = (unsigned char *)dst;
	src_tmp = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (dst_tmp <= src_tmp)
	{
		while (len--)
			*dst_tmp++ = *src_tmp++;
	}
	else
	{
		dst_tmp += (len - 1);
		src_tmp += (len - 1);
		while (len--)
			*dst_tmp-- = *src_tmp--;
	}
	return (dst);
}
