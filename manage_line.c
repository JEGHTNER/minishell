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
#include <stdio.h>

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
		insert_node("|", cmd, PIPE);
		(*idx)++;
	}
}

// static char	*quote_in_chunk(char *line, size_t *idx)
// {

// }

void	pipe_in_chunk(t_cmd *cmd, char *line, size_t *start, size_t *idx)
{
	char *tmp;

	tmp = strchop(line, *start, *idx);
	insert_node(tmp, cmd, WORD);
	manage_pipe(cmd, line, idx);
	*start = *idx;
}

void	manage_chunk(t_cmd *cmd, char *line, size_t *idx)
{
	char	*data;
	size_t	start_idx;

	start_idx = *idx;
	while ((is_whitespace(line[*idx]) == NO && line[*idx]))
	{
		if (line[*idx] == '|')
			pipe_in_chunk(cmd, line, &start_idx, idx);
		// else if (line[*idx] == '\'' || line[*idx] == '\"')
		// {
		// 	data = strchop(line, start_idx, *idx - 1);
		// 	data = ft_strjoin(data, quote_in_chunk(line, idx));
		// 	insert_node(data, cmd, WORD);
		// }
		(*idx)++;
		if (is_whitespace(line[*idx]) == YES || *idx == ft_strlen(line))
		{
			data = strchop(line, start_idx, *idx - 1);
			insert_node(data, cmd, WORD);
		}
	}
}
