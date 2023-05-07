/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:05:53 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:50 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*double_quote_to_string(t_cmd *cmd, char *line, size_t *idx, size_t *st)
{
	char	*to_ret;
	size_t	start;
	size_t	end_idx;

	end_idx = check_side_quotation(line, *idx);
	(*idx)++;
	start = *idx;
	if (nothing_to_ret(&to_ret, idx, end_idx, st) == YES)
		return (to_ret);
	while (*idx < end_idx)
	{
		if (line[*idx] == '$')
			to_ret = join_n_free(chop_n_trim(to_ret, line, &start, idx), \
					find_n_convert(cmd, line, idx, &start));
		else
			(*idx)++;
		if (*idx == end_idx)
			to_ret = chop_n_trim(to_ret, line, &start, idx);
	}
	*idx = end_idx + 1;
	*st = *idx;
	return (to_ret);
}

char	*single_quote_to_string(char *line, size_t *idx, size_t *st)
{
	char	*to_ret;
	size_t	start_idx;
	size_t	end_idx;

	to_ret = ft_strdup("");
	end_idx = check_side_quotation(line, *idx);
	if (nothing_to_ret(&to_ret, idx, end_idx, st) == YES)
		return (to_ret);
	start_idx = *idx + 1;
	to_ret = join_n_free(to_ret, strchop(line, start_idx, end_idx - 1));
	*idx = end_idx + 1;
	*st = *idx;
	return (to_ret);
}

static char	*trim_before_conv(char *data, char *line, size_t *st, size_t *idx)
{
	size_t	end_idx;
	char	*tmp;

	end_idx = *idx - 1;
	if (line[end_idx] == '\'' || line[end_idx] == '\"')
		return (data);
	else
	{
		tmp = strchop(line, *st, end_idx);
		data = join_n_free(data, tmp);
		return (data);
	}
}

static char	*check_remain_quote(t_cmd *cmd, char *line, size_t *idx)
{
	size_t	start_idx;
	char	*remain;

	start_idx = *idx;
	remain = ft_strdup("");
	if (*idx == ft_strlen(line) || is_whitespace(line[*idx]) == YES)
		return (remain);
	while (line[*idx] && is_whitespace(line[*idx]) == NO)
	{
		if (line[*idx] == '|' || line[*idx] == '>' || line[*idx] == '<')
			return (trim_before_conv(remain, line, &start_idx, idx));
		else if (line[*idx] == '\'' || line[*idx] == '\"')
			remain = join_n_free(chop_n_trim(remain, line, &start_idx, idx), \
				quote_to_string(cmd, line, idx, &start_idx));
		else if (line[*idx] == '$')
			remain = join_n_free(chop_n_trim(remain, line, &start_idx, idx), \
				find_n_convert(cmd, line, idx, &start_idx));
		else
			(*idx)++;
		if (*idx == ft_strlen(line) || is_whitespace(line[*idx]) == YES)
			remain = chop_n_trim(remain, line, &start_idx, idx);
	}
	return (remain);
}

void	manage_quotation(t_cmd *cmd, char *line, size_t *idx)
{
	size_t	start_idx;
	char	*data;

	start_idx = *idx;
	if (line[*idx] == '\"')
		data = double_quote_to_string(cmd, line, idx, &start_idx);
	else
		data = single_quote_to_string(line, idx, &start_idx);
	data = join_n_free(data, check_remain_quote(cmd, line, idx));
	insert_node(data, cmd, WORD);
}
