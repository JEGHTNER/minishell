/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:55:03 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 10:07:47 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t n)
{
	size_t	ind;

	ind = 0;
	while (ind < n)
	{
		if (((unsigned char *)ptr)[ind] == (unsigned char)c)
			return ((void *)ptr + ind);
		ind++;
	}
	return ((void *)0);
}
