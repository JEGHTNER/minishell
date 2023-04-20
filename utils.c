/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:27:12 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/17 15:27:14 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_macro is_everything_whitespace(char *tmp)
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
	exit(EXIT_FAILURE);
	return ;
}

char	*strchop(char *src, size_t start, size_t end)
{
	size_t	idx;
	char *	ret;

	idx = 0;
	ret = (char *)malloc(end - start + 1);
	if (!ret)
		return ((char *)0);
	while (idx <= end - start)
		ret = src[idx++];
	ret[end - start + 1] = '\0';
	return (ret);
}