/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:55:00 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/10 14:03:22 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ind;

	ind = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (ind < len && haystack[ind])
	{
		if (ft_strncmp(haystack + ind, needle, ft_strlen((char *)needle)) == 0)
		{
			if (len - ind >= ft_strlen((char *)needle))
				return ((char *)(haystack + ind));
		}
		ind++;
	}
	return (0);
}
