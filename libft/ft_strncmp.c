/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:54:05 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 12:09:10 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	ind;

	ind = 0;
	if (n == 0)
		return (0);
	while (ind < n && (s1[ind] || s2[ind]))
	{
		if (*(s1 + ind) != *(s2 + ind))
			return ((unsigned char) s1[ind] - (unsigned char) s2[ind]);
		ind++;
	}
	return (0);
}
