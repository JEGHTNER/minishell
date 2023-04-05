/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_hex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:34:37 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:03:07 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	display_hex(unsigned long long number, char *hex, int *count)
{
	if (number >= 16)
	{
		if (display_hex(number / 16, hex, count) == -1)
			return (-1);
	}
	if (write(1, &hex[number % 16], 1) == -1)
	{
		*count = -1;
		return (-1);
	}
	(*count)++;
	return (1);
}

int	ft_puthex_p(unsigned long long arg_ptr_hex)
{
	int		count;
	char	*low_hex;

	low_hex = "0123456789abcdef";
	if (write(1, "0x", 2) == -1)
		return (-1);
	count = 2;
	display_hex(arg_ptr_hex, low_hex, &count);
	return (count);
}

int	ft_puthex_x(char format, unsigned long long arg_ptr_hex)
{
	int		count;
	char	*carg_ptr_hex;
	char	*low_hex;

	count = 0;
	carg_ptr_hex = "0123456789ABCDEF";
	low_hex = "0123456789abcdef";
	if (format == 'x')
		display_hex(arg_ptr_hex, low_hex, &count);
	else
		display_hex(arg_ptr_hex, carg_ptr_hex, &count);
	return (count);
}

int	print_hexp(char format, va_list arg_ptr)
{
	int					count;
	unsigned long long	arg_ptr_hex;

	if (format == 'p')
	{
		arg_ptr_hex = (unsigned long long)va_arg(arg_ptr, void *);
		count = ft_puthex_p(arg_ptr_hex);
	}
	else
	{
		arg_ptr_hex = va_arg(arg_ptr, unsigned int);
		count = ft_puthex_x(format, arg_ptr_hex);
	}
	return (count);
}
