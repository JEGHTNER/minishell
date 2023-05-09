/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:24:19 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/08 05:02:03 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_words(char **words)
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

static	char	**case_no_equal(char const *string, int i)
{
	char	**words;

	if (ft_strlen(string) == i)
	{
		words = malloc(sizeof(char *) * 2);
		if (!words)
			return (0);
		words[0] = malloc(sizeof(char) * i + 1);
		if (!words[0])
			return (free_words(words));
		ft_strlcpy(words[0], string, i + 1);
		words[1] = NULL;
		return (words);
	}
	return (NULL);
}

static	char	**case_eqaul(char const *string, int i)
{
	char	**words;
	int		j;
	int		len;

	words = malloc(sizeof(char *) * 3);
	if (!words)
		return (NULL);
	len = i;
	words[0] = malloc(sizeof(char) * len + 1);
	if (!words[0])
		return (free_words(words));
	ft_strlcpy(words[0], string, len + 1);
	while (string[++i])
		j++;
	words[1] = malloc(sizeof(char) * j + 1);
	if (!words[1])
		return (free_words(words));
	ft_strlcpy(words[1], &string[len + 1], j + 1);
	words[2] = 0;
	return (words);
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
	words = case_no_equal(string, i);
	if (words != NULL)
		return (words);
	return (case_eqaul(string, i));
}
