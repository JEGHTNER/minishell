/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pointer_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:37:56 by joon-lee          #+#    #+#             */
/*   Updated: 2022/12/07 15:38:11 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	write_address(size_t addr, char *base, int *sum)
{
	if (!addr)
		return ;
	write_address(addr / 16, base, sum);
	write(1, &base[addr % 16], 1);
	(*sum)++;
}

int	change_pointer_add(void *p)
{
	int			sum;
	ssize_t		check;

	check = write(1, "0x", 2);
	if (check == -1)
		return (-1);
	sum = 2;
	if (!p)
	{
		check = write(1, "0", 1);
		if (check == -1)
			return (-1);
		return (3);
	}
	write_address((size_t)p, "0123456789abcdef", &sum);
	return (sum);
}
