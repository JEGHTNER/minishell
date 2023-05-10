/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:00:18 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 10:05:34 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	ind;

	ind = 0;
	if (!((unsigned char *)dst) && !(unsigned char *)src)
		return ((void *)0);
	if (dst >= src)
	{
		while (len)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}
	}
	else
	{
		while (len)
		{
			((unsigned char *)dst)[ind] = ((unsigned char *)src)[ind];
			ind++;
			len--;
		}
	}
	return ((void *)dst);
}
