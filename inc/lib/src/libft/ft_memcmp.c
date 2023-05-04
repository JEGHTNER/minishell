/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:44:38 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:17:07 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_memcmp(const void *string1, const void *string2, size_t n)
{
	size_t				i;
	unsigned char		*s1_tmp;
	unsigned char		*s2_tmp;

	s1_tmp = (unsigned char *)string1;
	s2_tmp = (unsigned char *)string2;
	i = 0;
	while (i < n)
	{
		if (s1_tmp[i] != s2_tmp[i])
			return (s1_tmp[i] - s2_tmp[i]);
		i++;
	}
	return (0);
}
