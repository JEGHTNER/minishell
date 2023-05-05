/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:24:19 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/05 18:59:53 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	**free_all(char **words)
// {
// 	int	i;

// 	i = 0;
// 	while (words[i])
// 	{
// 		free(words[i]);
// 		i++;
// 	}
// 	free(words);
// 	return (0);
// }

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

char	**ft_split_export(char const *string, char seperator)
{
	int		i;
	int		j;
	int		len;
	char	**words;

	i = -1;
	j = 0;
	while (string[++i])
	{
		if (string[i] == seperator)
			break ;
	}
	if (ft_strlen(string) == i)
	{
		words = malloc(sizeof(char *) * 2);
		if (!words)
			return (0);
		words[0] = malloc(sizeof(char) * i + 1);
		ft_strlcpy(words[0], string, i + 1);
		words[1] = NULL;
		return (words);
	}
	words = malloc(sizeof(char *) * 3);
	if (!words)
		return (0);
	len = i;
	words[0] = malloc(sizeof(char) * len + 1);
	ft_strlcpy(words[0], string, len + 1);
	while (string[++i])
		j++;
	words[1] = malloc(sizeof(char) * j + 1);
	ft_strlcpy(words[1], &string[len + 1], j + 1);
	words[2] = 0;
	return (words);
}
