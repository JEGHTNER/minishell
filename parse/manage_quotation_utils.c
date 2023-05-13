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

t_macro	check_side_quotation(char *line, size_t *start, size_t *end_idx)
{
	size_t	idx;
	size_t	end;
	char	quote;

	idx = *start;
	quote = line[*start];
	end = ft_strlen(line);
	if (ft_strlen(line) == 1)
	{
		(*start)++;
		return (error_n_ret("syntax error: quotation can't find the match\n"));
	}
	while (idx < end)
	{
		if (*start != idx && line[idx] == quote)
			break ;
		idx++;
	}
	*end_idx = idx;
	if (idx == end)
	{
		*start = end;
		return (error_n_ret("syntax error: quotation can't find the match\n"));
	}
	return (YES);
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
