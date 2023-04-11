/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:14:54 by joon-lee          #+#    #+#             */
/*   Updated: 2022/12/07 16:09:45 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	find_proper_conversion(const char *format, va_list ap)
{
	ssize_t	check;

	if (*format == 'c')
		return (change_char(va_arg(ap, unsigned int)));
	else if (*format == 's')
		return (change_string(va_arg(ap, char *)));
	else if (*format == 'p')
		return (change_pointer_add(va_arg(ap, void *)));
	else if (*format == 'd' || *format == 'i')
		return (change_integar_decimal(va_arg(ap, unsigned int)));
	else if (*format == 'u')
		return (change_unsigned_int(va_arg(ap, unsigned int)));
	else if (*format == 'x' || *format == 'X')
		return (change_hexadecimal(va_arg(ap, unsigned int), *format));
	else if (*format == '%')
	{
		check = write(1, "%", 1);
		if (check == -1)
			return (-1);
		return (1);
	}
	else
		return (-1);
}

static int	conversion_distinguish(const char *fmt, va_list ap, long *val)
{
	int	len;

	len = find_proper_conversion(fmt, ap);
	if (len == -1)
		return (1);
	*val += len;
	if (*val > 2137483647)
		return (1);
	return (0);
}

static int	change_into(const char *format, va_list ap)
{
	long	val;
	int		err_find;
	ssize_t	check;

	val = 0;
	while (*format)
	{
		if (*format == '%')
		{
			err_find = conversion_distinguish(++format, ap, &val);
			if (err_find)
				return (-1);
		}
		else
		{
			if (val > 2147483647)
				return (-1);
			check = write(1, format, 1);
			if (check == -1)
				return (-1);
			val++;
		}
		format++;
	}
	return (val);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		rtrn_val;

	rtrn_val = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	rtrn_val = change_into((char *)format, ap);
	if (rtrn_val == -1)
		return (-1);
	va_end(ap);
	return (rtrn_val);
}
