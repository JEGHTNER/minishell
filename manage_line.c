/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:54 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/17 15:26:55 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_pipe(t_cmd *cmd, char *line, size_t *idx, size_t *quote)
{
	if (cmd->chunk_head == 0)
		ft_exit_with_error("syntax error near unexpected token : ", " | ");
	else
	{
		if (line[*idx + 1] == '|')
			ft_exit_with_error("syntax error", "||");
		if (line[*idx + 1] == '\0')
			ft_exit_with_error("syntax error for pipe", 0);
		insert_node("|", cmd);
		(*idx)++;
	}
}

void	manage_chunk(t_cmd *cmd, char *line, size_t *idx)
{
	char	*data;
	size_t	start_idx;
	size_t	end_idx;

	start_idx = *idx;
	while (is_whitespace(line[*idx]) == NO)
		(*idx)++;
	end_idx = *idx - 1;
	data = strchop(line, start_idx, end_idx);
	insert_node(data, cmd);
}
