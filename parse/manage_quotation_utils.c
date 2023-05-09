/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:16:07 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:47 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_side_quotation(char *line, size_t start)
{
	size_t	idx;
	size_t	end;
	char	quote;

	idx = start;
	quote = line[start];
	end = ft_strlen(line);
	if (ft_strlen(line) == 1)
		ft_exit_with_error("syntax error: quotation can't find the match", 0);
	while (idx < end)
	{
		if (start != idx && line[idx] == quote)
			break ;
		idx++;
	}
	if (idx == end)
		ft_exit_with_error("syntax error: quotation can't find the match", 0);
	return (idx);
}

char	*quote_to_string(t_cmd *cmd, char *line, size_t *idx, size_t *st)
{
	if (line[*idx] == '\"')
		return (double_quote_to_string(cmd, line, idx, st));
	else
		return (single_quote_to_string(line, idx, st));
}

t_macro	nothing_to_ret(char **tmp, size_t *idx, size_t end_idx, size_t *st)
{
	*tmp = ft_strdup("");
	if (*idx == end_idx)
	{
		(*idx)++;
		*st = *idx;
		return (YES);
	}
	return (NO);
}
