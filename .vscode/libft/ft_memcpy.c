/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:00:48 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 10:06:09 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	ind;

	ind = 0;
	if (!((unsigned char *)dst) && !(unsigned char *)src)
		return ((void *)0);
	while (ind < n)
	{
		((unsigned char *)dst)[ind] = ((unsigned char *)src)[ind];
		ind++;
	}
	return ((void *)dst);
}
