/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:29:35 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:17:19 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static char	*string_big_case(char const *string, unsigned int start, size_t len)
{
	char	*tmp_string;
	size_t	str_length;

	str_length = ft_strlen(string);
	len = str_length;
	if (!string)
		return (0);
	if (start >= str_length)
		return (ft_strdup(""));
	tmp_string = malloc(sizeof(char) * (len - start + 1));
	if (!tmp_string)
		return (0);
	ft_strlcpy(tmp_string, &string[start], len + 1);
	return (tmp_string);
}

char	*ft_substr(char const *string, unsigned int start, size_t len)
{
	char	*tmp_string;
	size_t	str_length;

	str_length = ft_strlen(string);
	if (len > str_length)
	{
		tmp_string = string_big_case(string, start, len);
		return (tmp_string);
	}
	if (!string)
		return (0);
	if (start >= str_length)
		return (ft_strdup(""));
	if (str_length - start < len)
		len = str_length - start;
	tmp_string = malloc(sizeof(char) * (len + 1));
	if (!tmp_string)
		return (0);
	ft_strlcpy(tmp_string, &string[start], len + 1);
	return (tmp_string);
}
