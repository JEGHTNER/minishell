/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:39:59 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:00:11 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

size_t	ft_strlen(const char *string);
char	*ft_strchr(const char *string, int c);
int		print_percent(void);
int		print_c(va_list arg_ptr);
int		print_s(va_list arg_ptr);
int		display(long long number, int *count);
int		ft_putnbr_di(int number);
int		print_di(va_list arg_ptr);
int		print_u(va_list arg_ptr);
int		display_hex(unsigned long long number, char *hex, int *count);
int		ft_puthex_p(unsigned long long arg_ptr_hex);
int		ft_puthex_x(char format, unsigned long long arg_ptr_hex);
int		print_hexp(char format, va_list arg_ptr);
int		print_argument(char format, va_list arg_ptr);
int		init_parse(char *format, int *idx_ptr, va_list arg_ptr);
int		parse_format(char *format, va_list arg_ptr);
int		ft_printf(const char *format, ...);

#endif