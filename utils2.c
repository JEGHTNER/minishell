/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:02:08 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/27 13:02:09 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	cmd_init(t_cmd *cmd)
{
    cmd->env_head = 0;
	cmd->chunk_head = 0;
	cmd->tree_head = 0;
}

// char	*chop_n_trim(char *line, size_t *start_idx, size_t *idx, char *data)
// {
// 	char	*tmp;

// 	tmp = strchop(line, start_idx, *idx - 1);
// 	data =
// }
