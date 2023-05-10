/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:36:52 by joon-lee          #+#    #+#             */
/*   Updated: 2022/12/07 16:01:25 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	change_char(char c)
{
	ssize_t	check;

	check = write(1, &c, 1);
	if (check == -1)
		return (-1);
	return (check);
}
