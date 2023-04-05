/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:18:47 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:17:14 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *string, void (*f)(unsigned int, char*))
{
	int	i;

	if (!string || !(f))
		return ;
	i = 0;
	while (string[i])
	{
		f(i, &string[i]);
		i++;
	}
}
