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

int	ft_strncmp(const char *string1, const char *string2, size_t len)
{
	if (string1 == NULL)
		return (0);
	while ((*string1 || *string2) && len-- > 0)
	{
		if (*string1 != *string2)
			return ((unsigned char)*string1 - (unsigned char )*string2);
		string1++;
		string2++;
	}
	return (0);
}

