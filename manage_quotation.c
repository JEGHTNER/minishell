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

static size_t	check_side_quotation(char *line, size_t start)
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

char	*quotation_to_string(char *line, size_t *idx)
{
	char	*tmp;
	char	*to_ret;
	size_t	start_idx;
	size_t	end_idx;

	to_ret = ft_strdup("");
	end_idx = check_side_quotation(line, *idx);
	if (*idx + 1 == end_idx)
	{
		*idx = end_idx + 1;
		return (to_ret);
	}
	start_idx = *idx + 1;
	tmp = strchop(line, start_idx, end_idx - 1);
	to_ret = ft_strjoin(to_ret, tmp);
	*idx = end_idx + 1;
    return (to_ret);
}

char	*pipe_after_quote(char *data, char *line, size_t *idx)
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
		data = ft_strjoin(data, tmp);
		return (data);
	}
}

char	*check_remain(t_cmd *cmd, char *line, size_t *idx, char *data)
{
	size_t	start_idx;
	char	*tmp;

	start_idx = *idx;
	if (*idx == ft_strlen(line))
		return (data);
	while (line[*idx] && is_whitespace(line[*idx]) == NO)
	{
		if (line[*idx] == '|')
			return (pipe_after_quote(data, line, idx));
		else if (line[*idx] == '\'' || line[*idx] == '\"')
		{
			tmp = strchop(line, start_idx, *idx - 1);
			data = ft_strjoin(tmp, quotation_to_string(line, idx));
			start_idx = *idx;
		}
		else if (line[*idx]== '$')
		{
			tmp = find_n_convert(cmd, line, idx);
		}
		else
			(*idx)++;
		if (is_whitespace(line[*idx]) == YES || *idx == ft_strlen(line))
		{
			tmp = strchop(line, start_idx, *idx - 1);
			data = ft_strjoin(data, tmp);
		}
	}
	return (data);
}

void	manage_quotation(t_cmd *cmd, char *line, size_t *idx)
{
	char	*data;
	char	quote;

	quote = line[*idx];
    data = quotation_to_string(line, idx);
	data = check_remain(cmd, line, idx, data);
	if (quote == '\'')
		insert_node(data, cmd, W_SINGLE);
	else
		insert_node(data, cmd, W_DOUBLE);
}
