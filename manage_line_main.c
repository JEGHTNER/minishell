/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:41 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/23 12:23:51 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	line_parse(t_cmd *cmd, char *line)
{
	size_t	idx;

	idx = 0;
	while (line[idx])
	{
		if (line[idx] == '|')
			manage_pipe(cmd, line, &idx);
		else if (line[idx] == '\'' || line[idx] == '\"')
			manage_quotation(cmd, line, &idx);
		else if (line[idx] == '\\' || line[idx] == ';')
			ft_exit_with_error("syntax error near unexpected token\n", line);
		else if (line[idx] == '>' || line[idx] == '<')
			manage_redir(cmd, line, &idx);
		else if (line[idx] == '$')
			manage_env(cmd, line, &idx);
		else if (is_whitespace(line[idx]) == YES)
			idx++;
		else
			manage_chunk(cmd, line, &idx);
	}
}
