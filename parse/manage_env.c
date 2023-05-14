/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:37:38 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 22:40:31 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_exit_stat(size_t *idx, size_t *st)
{
	char	*to_ret;
	char	*tmp;

	tmp = ft_itoa(g_exit_status);
	to_ret = ft_strdup(tmp);
	(*idx)++;
	*st = *idx;
	free(tmp);
	return (to_ret);
}

char	*convert_null(size_t *idx, size_t *st)
{
	(*idx)++;
	*st = *idx;
	return (ft_strdup(""));
}

char	*find_n_convert(t_cmd *cmd, char *line, size_t *idx, size_t *st)
{
	char	*key;
	char	*to_ret;
	size_t	end_idx;

	(*idx)++;
	end_idx = *idx;
	if (*idx == ft_strlen(line) || is_whitespace(line[*idx]) == YES
		|| is_it_in_charset(line[*idx], "./`~!#^&%%*(){}\\|\'\";") == YES)
	{
		*st = *idx;
		return (ft_strdup("$"));
	}
	if (line[*idx] == '?')
		return (convert_exit_stat(idx, st));
	if (line[*idx] == '$')
		return (convert_null(idx, st));
	while (is_it_env_key(line[end_idx]) == YES)
		end_idx++;
	key = strchop(line, *idx, end_idx - 1);
	to_ret = find_value_with_key(cmd->env_head, key);
	*idx = end_idx;
	*st = *idx;
	free(key);
	return (to_ret);
}

static char	*check_remain_env(t_cmd *cmd, char *line, size_t *idx)
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

t_macro	manage_env(t_cmd *cmd, char *line, size_t *idx)
{
	size_t	start_idx;
	char	*data;

	start_idx = 0;
	data = find_n_convert(cmd, line, idx, &start_idx);
	data = join_n_free(data, check_remain_env(cmd, line, idx));
	insert_node(data, cmd, WORD);
	return (YES);
}
