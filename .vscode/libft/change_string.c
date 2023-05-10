/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:37:01 by joon-lee          #+#    #+#             */
/*   Updated: 2022/12/07 14:53:02 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	change_string(char *str)
{
	ssize_t		check;
	long		sum;

	sum = 0;
	if (!str)
	{
		check = write(1, "(null)", 6);
		if (check == -1)
			return (-1);
		return (6);
	}
	while (*str)
	{
		if (sum == 2147483647)
			return (-1);
		check = write(1, str, 1);
		if (check == -1)
			return (-1);
		sum++;
		str++;
	}
	return (sum);
}
