/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:24:19 by jehelee           #+#    #+#             */
/*   Updated: 2023/01/07 19:17:12 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static char	**free_all(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}

static int	check_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	count_words(char const *string, char seperator)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string[i])
	{
		while (string[i] && check_sep(string[i], seperator))
			i++;
		if (string[i])
			count++;
		while (string[i] && !check_sep(string[i], seperator))
			i++;
	}
	return (count);
}

static char	*make_string(char const *string, char seperator)
{
	char	*tmp_string;
	int		len;

	len = 0;
	while (string[len] && string[len] != seperator)
		len++;
	tmp_string = malloc(sizeof(char) * len + 1);
	if (!tmp_string)
		return (0);
	ft_strlcpy(tmp_string, string, len + 1);
	return (tmp_string);
}

char	**ft_split(char const *string, char seperator)
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	j = 0;
	words = malloc(sizeof(char *) * (count_words(string, seperator) + 1));
	if (!words)
		return (0);
	while (string[i])
	{
		while (string[i] && check_sep(string[i], seperator))
			i++;
		if (string[i] && check_sep(string[i], seperator) == 0)
		{
			words[j] = make_string(&string[i], seperator);
			if (!words[j])
				return (free_all(words));
			j++;
		}
		while (string[i] && check_sep(string[i], seperator) == 0)
			i++;
	}
	words[j] = 0;
	return (words);
}
