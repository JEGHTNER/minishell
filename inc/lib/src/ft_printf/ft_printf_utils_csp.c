/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_csp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:34:35 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:03:08 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	print_percent(void)
{
	int	count;

	count = 0;
	if (write(1, "%", 1) == -1)
		return (-1);
	count++;
	return (count);
}

int	print_c(va_list arg_ptr)
{
	int				count;
	unsigned char	arg_ptr_char;

	count = 0;
	arg_ptr_char = (unsigned char)va_arg(arg_ptr, int);
	if (write(1, &arg_ptr_char, 1) == -1)
		return (-1);
	count++;
	return (count);
}

int	print_s(va_list arg_ptr)
{
	int		count;
	char	*arg_ptr_str;

	count = 0;
	arg_ptr_str = va_arg(arg_ptr, char *);
	if (!arg_ptr_str)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		count = 6;
		return (count);
	}
	count = ft_strlen(arg_ptr_str);
	if (write(1, arg_ptr_str, count) == -1)
		return (-1);
	return (count);
}
