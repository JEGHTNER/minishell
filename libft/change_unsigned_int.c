/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_unsigned_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:37:43 by joon-lee          #+#    #+#             */
/*   Updated: 2022/12/07 15:13:40 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_putchar_ui(char c, ssize_t *flag)
{
	*flag = write(1, &c, 1);
}

static void	ft_putnbr_ui(unsigned int n, int *sum, ssize_t *flag)
{
	if (n >= 10)
	{
		ft_putnbr_ui(n / 10, sum, flag);
		if (*flag == -1)
			return ;
		ft_putnbr_ui(n % 10, sum, flag);
	}
	else
	{
		ft_putchar_ui(n + 48, flag);
		if (*flag == -1)
			return ;
		(*sum)++;
	}
}

int	change_unsigned_int(unsigned int ui)
{
	int		sum;
	ssize_t	flag;

	sum = 0;
	flag = 1;
	ft_putnbr_ui(ui, &sum, &flag);
	if (flag == -1)
		return (-1);
	return (sum);
}
