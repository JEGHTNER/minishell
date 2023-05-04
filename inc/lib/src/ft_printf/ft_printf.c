/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:34:28 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:03:10 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	print_argument(char format, va_list arg_ptr)
{
	int	count;

	count = 0;
	if (format == '%')
		count = print_percent();
	else if (format == 'd' || format == 'i')
		count = print_di(arg_ptr);
	else if (format == 'u')
		count = print_u(arg_ptr);
	else if (format == 'x' || format == 'X' || format == 'p')
		count = print_hexp(format, arg_ptr);
	else if (format == 'c')
		count = print_c(arg_ptr);
	else if (format == 's')
		count = print_s(arg_ptr);
	return (count);
}

int	init_parse(char *string, int *idx_ptr, va_list arg_ptr)
{
	int	count;
	int	check_error;

	count = 0;
	check_error = 0;
	(*idx_ptr)++;
	if (ft_strchr("cspdiuxX%", string[*idx_ptr]))
	{
		check_error = print_argument(string[*idx_ptr], arg_ptr);
		if (check_error == -1)
			return (-1);
		count += check_error;
	}
	return (count);
}

int	parse_format(char *string, va_list arg_ptr)
{
	int	ret_size;
	int	idx;
	int	*idx_ptr;
	int	check_error;

	ret_size = 0;
	idx = -1;
	idx_ptr = &idx;
	while (string[++idx])
	{
		if (string[idx] == '%')
		{
			check_error = init_parse(string, idx_ptr, arg_ptr);
			if (check_error == -1)
				return (-1);
			ret_size += check_error;
		}
		else
		{
			if (write(1, &string[idx], 1) == -1)
				return (-1);
			ret_size++;
		}
	}
	return (ret_size);
}

int	ft_printf(const char *string, ...)
{
	int		ret_size;
	va_list	arg_ptr;

	va_start(arg_ptr, string);
	ret_size = parse_format((char *)string, arg_ptr);
	va_end(arg_ptr);
	return (ret_size);
}
