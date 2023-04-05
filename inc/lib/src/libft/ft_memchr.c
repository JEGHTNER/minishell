/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:40:59 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:17:06 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memchr(const void *ptr, int c, size_t len)
{
	unsigned char	*tmp_ptr;
	unsigned char	tmp_c;
	size_t			i;

	tmp_ptr = (unsigned char *)ptr;
	tmp_c = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		if (tmp_ptr[i] == tmp_c)
			return (&tmp_ptr[i]);
		i++;
	}
	return (0);
}
