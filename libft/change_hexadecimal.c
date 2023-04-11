/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_hexadecimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:37:24 by joon-lee          #+#    #+#             */
/*   Updated: 2022/12/07 16:02:06 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	hexa_change(unsigned int temp, char *base, int *sum, ssize_t *check)
{
	if (!temp)
		return ;
	hexa_change(temp / 16, base, sum, check);
	if (*check == -1)
		return ;
	*check = write(1, &base[temp % 16], 1);
	if (*check == -1)
		return ;
	(*sum)++;
}

int	change_hexadecimal(unsigned int hexa, char d)
{
	int		sum;
	ssize_t	check;

	sum = 0;
	check = 1;
	if (hexa == 0)
	{
		check = write(1, "0", 1);
		if (check == -1)
			return (-1);
		return (1);
	}
	if (d == 'x')
		hexa_change(hexa, "0123456789abcdef", &sum, &check);
	else
		hexa_change(hexa, "0123456789ABCDEF", &sum, &check);
	if (check == -1)
		return (-1);
	return (sum);
}
