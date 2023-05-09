/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:27:12 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:29 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_macro	is_everything_whitespace(char *tmp)
{
	while (*tmp)
	{
		if (is_whitespace(*tmp) == NO)
			return (NO);
		tmp++;
	}
	return (YES);
}

t_macro	is_whitespace(char tmp)
{
	if ((tmp >= 9 && tmp <= 13) || tmp == 32)
		return (YES);
	else
		return (NO);
}

void	ft_exit_with_error(char *message, char *specifier)
{
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(specifier, STDERR_FILENO);
	exit(EXIT_FAILURE);
	return ;
}

char	*strchop(char *src, size_t start, size_t end)
{
	size_t	idx;
	char	*ret;

	idx = 0;
	if (end < start)
		return (ft_strdup(""));
	ret = (char *)malloc(end - start + 2);
	if (!ret)
		ft_exit_with_error("malloc error", 0);
	while (idx <= end - start)
	{
		ret[idx] = src[start + idx];
		idx++;
	}
	ret[end - start + 1] = '\0';
	return (ret);
}
