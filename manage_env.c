/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:37:38 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/26 18:37:39 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*find_n_convert(t_cmd *cmd, char *line, size_t *idx)
{
	char	*key;
	char	*to_ret;
	size_t	end_idx;

	(*idx)++;
	end_idx = *idx;
	if (*idx == ft_strlen(line) || is_whitespace(line[*idx]) == YES)
		return ("$");
	while (is_it_env_key(line[end_idx]) == YES)
		end_idx++;
	key = strchop(line, *idx, end_idx - 1);
	to_ret = find_value_with_key(cmd->env_head, key);
	*idx = end_idx;
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
			return (remain);
		else if (line[*idx] == '\'' || line[*idx] == '\"')
			remain = ft_strjoin(chop_n_trim(remain, line, &start_idx, idx), \
				quote_to_string(cmd, line, idx, &start_idx));
		else if (line[*idx]== '$')
			remain = ft_strjoin(chop_n_trim(remain, line, &start_idx, idx), \
				find_n_convert(cmd, line, idx));
		else
			(*idx)++;
		if (is_whitespace(line[*idx]) == YES || *idx == ft_strlen(line))
			remain = chop_n_trim(remain, line, &start_idx, idx);
	}
	return (remain);
}

void	manage_env(t_cmd *cmd, char *line, size_t *idx)
{
	char	*data;

	data = find_n_convert(cmd, line, idx);
	data = ft_strjoin(data, check_remain_env(cmd, line, idx));
	insert_node(data, cmd, WORD);
}
