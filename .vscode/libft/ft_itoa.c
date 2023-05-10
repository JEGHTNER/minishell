/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:16:50 by joon-lee          #+#    #+#             */
/*   Updated: 2022/11/14 15:12:58 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_len_count(long long n)
{
	size_t	temp;

	temp = 1;
	while (n / 10)
	{
		temp++;
		n /= 10;
	}
	return (temp);
}

static char	*ft_neg_change(int n)
{
	char		*neg;
	size_t		rv_ind;
	long long	temp;

	temp = (long long)n * -1;
	rv_ind = ft_len_count(temp);
	neg = (char *)malloc(sizeof(char) * (rv_ind + 2));
	if (!neg)
		return (0);
	neg[0] = '-';
	neg[rv_ind + 1] = '\0';
	while (rv_ind)
	{
		neg[rv_ind] = temp % 10 + '0';
		temp /= 10;
		rv_ind--;
	}
	return (neg);
}

static char	*ft_pos_change(int n)
{
	char	*pos;
	size_t	rv_ind;

	rv_ind = ft_len_count(n);
	pos = (char *)malloc(sizeof(char) * (ft_len_count(n) + 1));
	if (!pos)
		return (0);
	pos[rv_ind] = '\0';
	while (rv_ind)
	{
		pos[rv_ind - 1] = n % 10 + '0';
		n /= 10;
		rv_ind--;
	}
	return (pos);
}

char	*ft_itoa(int n)
{
	char	*temp;

	if (n < 0)
		temp = ft_neg_change(n);
	else if (n == 0)
	{
		temp = (char *)malloc(sizeof(char) * 2);
		if (!temp)
			return (0);
		temp[0] = '0';
		temp[1] = '\0';
	}
	else
		temp = ft_pos_change(n);
	return (temp);
}
