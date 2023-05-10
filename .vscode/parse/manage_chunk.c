/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:54 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:39 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*chunk_to_string(char *line, size_t *idx)
{
	char	*tmp;
	char	*to_ret;
	size_t	start_idx;

	tmp = ft_strdup("");
	start_idx = *idx;
	while (is_it_env_key(line[*idx]) == YES)
		(*idx)++;
	to_ret = chop_n_trim(tmp, line, &start_idx, idx);
	return (to_ret);
}

char	*check_remain_chunk(t_cmd *cmd, char *line, size_t *idx)
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
			return (remain);
		else if (line[*idx] == '\'' || line[*idx] == '\"')
			remain = join_n_free(chop_n_trim(remain, line, &start_idx, idx), \
				quote_to_string(cmd, line, idx, &start_idx));
		else if (line[*idx] == '$')
			remain = join_n_free(chop_n_trim(remain, line, &start_idx, idx), \
				find_n_convert(cmd, line, idx, &start_idx));
		else
			(*idx)++;
		if (is_whitespace(line[*idx]) == YES || *idx == ft_strlen(line))
			remain = chop_n_trim(remain, line, &start_idx, idx);
	}
	return (remain);
}

void	manage_chunk(t_cmd *cmd, char *line, size_t *idx)
{
	char	*data;

	data = chunk_to_string(line, idx);
	data = join_n_free(data, check_remain_chunk(cmd, line, idx));
	insert_node(data, cmd, WORD);
}
