/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_integar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:37:36 by joon-lee          #+#    #+#             */
/*   Updated: 2022/12/07 16:03:19 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_putchar(char c, ssize_t *flag)
{
	*flag = write(1, &c, 1);
}

static void	ft_putnbr(int n, int *sum, ssize_t *flag)
{
	long	z;

	if (n < 0 && n > -2147483648)
	{
		*flag = write(1, "-", 1);
		if (*flag == -1)
			return ;
		(*sum)++;
		z = n * (-1);
		ft_putnbr(z, sum, flag);
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, sum, flag);
		if (*flag == -1)
			return ;
		ft_putnbr(n % 10, sum, flag);
	}
	else if (n < 10 && n >= 0)
	{
		ft_putchar(n + 48, flag);
		if (*flag == -1)
			return ;
		(*sum)++;
	}
}

int	change_integar_decimal(int i)
{
	int		sum;
	ssize_t	flag;

	sum = 0;
	flag = 1;
	if (i == -2147483648)
	{
		flag = write(1, "-2147483648", 11);
		if (flag == -1)
			return (-1);
		else
			return (11);
	}
	ft_putnbr(i, &sum, &flag);
	if (flag == -1)
		return (-1);
	return (sum);
}
