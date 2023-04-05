/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:43:33 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:16:58 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*new_space;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	new_space = malloc(size * count);
	if (!new_space)
		return (0);
	ft_bzero(new_space, size * count);
	return (new_space);
}
