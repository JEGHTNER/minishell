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
	while (line[end_idx] && is_whitespace(line[end_idx]) == NO
			&& !(line[end_idx] == '\"' || line[end_idx] == '\''
			|| line[end_idx] == '|' || line[end_idx] == '>'
			|| line[end_idx] == '<'))
		end_idx++;
	key = strchop(line, *idx, end_idx);
	to_ret = find_value_with_key(cmd->env_head, key);
	*idx = end_idx;
	return (to_ret);
}

char	*check_remain_env(t_cmd *cmd, char *line, size_t *idx, char *data)
{
	if (*idx == ft_strlen(line) || is_whitespace(line[*idx] == YES))
		return (data);
	while (line[*idx] && is_whitespace(line[*idx]) == NO)
	{
		if (line[*idx] == '|')
			return (data);
		
	}
}

void	manage_env(t_cmd *cmd, char *line, size_t *idx)
{
	char	*data;

	data = find_n_convert(cmd, line, idx);
	data = check_remain_env(cmd, line, idx, data);
	insert_node(data, cmd, WORD);
}
