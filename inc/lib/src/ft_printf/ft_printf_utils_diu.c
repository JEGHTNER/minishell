/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_diu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:39:36 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:03:07 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	display(long long number, int *count)
{
	long long	wr_num;

	if (number >= 10)
		if (display(number / 10, count) == -1)
			return (-1);
	wr_num = number % 10 + '0';
	if (write(1, &wr_num, 1) == -1)
	{
		*count = -1;
		return (-1);
	}
	(*count)++;
	return (1);
}

int	ft_putnbr_u(unsigned int number)
{
	int			count;

	count = 0;
	display(number, &count);
	return (count);
}

int	ft_putnbr_di(int number)
{
	long long	nbr;
	int			count;

	count = 0;
	nbr = (long long)number;
	if (nbr < 0)
	{
		nbr *= -1;
		if (write(1, "-", 1) == -1)
			return (-1);
		count++;
	}
	if (display(nbr, &count) == -1)
		return (-1);
	return (count);
}

int	print_di(va_list arg_ptr)
{
	int	count;
	int	arg_ptr_int;

	arg_ptr_int = va_arg(arg_ptr, int);
	count = ft_putnbr_di(arg_ptr_int);
	return (count);
}

int	print_u(va_list arg_ptr)
{
	int				count;
	unsigned int	arg_ptr_uint;

	arg_ptr_uint = va_arg(arg_ptr, unsigned int);
	count = ft_putnbr_u(arg_ptr_uint);
	return (count);
}
