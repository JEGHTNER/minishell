/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:02:08 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/04 14:59:25 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_init(t_cmd *cmd)
{
	cmd->env_head = 0;
	cmd->chunk_head = 0;
	cmd->tree_head = 0;
}

char	*chop_n_trim(char *remain, char *line, size_t *start_idx, size_t *idx)
{
	char	*to_ret;

	if (*start_idx == *idx)
		return (remain);
	to_ret = strchop(line, *start_idx, *idx - 1);
	if (remain == 0)
		return (to_ret);
	to_ret = join_n_free(remain, to_ret);
	*start_idx = *idx;
	return (to_ret);
}

char	*join_n_free(char *former, char *latter)
{
	char	*to_ret;
	char	*one_to_free;
	char	*two_to_free;

	one_to_free = former;
	two_to_free = latter;
	to_ret = ft_strjoin(former, latter);
	free(one_to_free);
	one_to_free = 0;
	free(two_to_free);
	two_to_free = 0;
	return (to_ret);
}
