/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:05:53 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/23 13:05:57 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*double_quote_to_string(t_cmd *cmd, char *line, size_t *idx, size_t *st)
{
	char	*to_ret;
	size_t	start_idx;
	size_t	end_idx;

	end_idx = check_side_quotation(line, *idx);
	(*idx)++;
	start_idx = *idx;
	if (nothing_to_ret(&to_ret, idx, end_idx) == YES) //이 경우 제외 따옴표 사이 문자 무조건 존재
		return (to_ret);
	while (*idx < end_idx)
	{
		if (line[*idx] == '$')
		{
			to_ret = chop_n_trim(to_ret, line, &start_idx, idx);
			to_ret = join_n_free(to_ret, find_n_convert(cmd, line, idx, &start_idx));
			start_idx = *idx;
		}
		else
			(*idx)++;
		if (*idx == end_idx)
			to_ret = chop_n_trim(to_ret, line, &start_idx, idx);
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
	if (*idx + 1 == end_idx) //이 경우 제외 따옴표 사이 문자 무조건 존재
	{
		*idx = end_idx + 1;
		return (to_ret);
	}
	start_idx = *idx + 1;
	to_ret = join_n_free(to_ret, strchop(line, start_idx, end_idx - 1));
	*idx = end_idx + 1;
	*st = *idx;
	return (to_ret);
}

static char	*trim_before_conv(char *data, char *line, size_t *idx)
{
	size_t	start_idx;
	size_t	end_idx;
	char	*tmp;

	start_idx = *idx - 1;
	end_idx = *idx - 1;
	if (line[end_idx] == '\'' || line[end_idx] == '\"')
		return (data);
	else
	{
		while (line[start_idx]
				&& !(line[start_idx] == '\'' || line[start_idx] == '\"'))
			start_idx--;
		start_idx++;
		tmp = strchop(line, start_idx, end_idx);
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
			return (trim_before_conv(remain, line, idx));
		else if (line[*idx] == '\'' || line[*idx] == '\"')
			remain = join_n_free(chop_n_trim(remain, line, &start_idx, idx), \
				quote_to_string(cmd, line, idx, &start_idx));
		else if (line[*idx]== '$')
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
