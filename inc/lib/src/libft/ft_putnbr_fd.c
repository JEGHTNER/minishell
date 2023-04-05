/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:48:23 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:17:11 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	display(long long number, int file_descriptor)
{
	if (number >= 10)
		display(number / 10, file_descriptor);
	ft_putchar_fd(number % 10 + '0', file_descriptor);
}

void	ft_putnbr_fd(int number, int file_descriptor)
{
	long long	nbr;

	nbr = (long long) number;
	if (file_descriptor < 0)
		return ;
	if (nbr < 0)
	{
		nbr *= -1;
		ft_putchar_fd('-', file_descriptor);
	}
	display(nbr, file_descriptor);
}
