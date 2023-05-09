/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:24:06 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:06:11 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_pipe(t_cmd *cmd, char *line, size_t *idx)
{
	if (cmd->chunk_head == 0)
		ft_exit_with_error("syntax error near unexpected token : ", " | ");
	else
	{
		if (line[*idx + 1] == '|')
			ft_exit_with_error("syntax error", "||");
		if (line[*idx + 1] == '\0')
			ft_exit_with_error("syntax error for pipe", 0);
		insert_node(ft_strdup("|"), cmd, PIPE);
		(*idx)++;
	}
}
