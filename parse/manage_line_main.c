/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_line_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:41 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/10 20:05:35 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_macro	line_parse(t_cmd *cmd, char *line)
{
	size_t	idx;

	idx = 0;
	while (line[idx])
	{
		if (line[idx] == '|' && manage_pipe(cmd, line, &idx) == NO)
			return (NO);
		else if ((line[idx] == '\'' || line[idx] == '\"')
			&& manage_quotation(cmd, line, &idx) == NO)
			return (NO);
		else if (line[idx] == '\\' || line[idx] == ';')
			return (error_n_ret("syntax error near unexpected token\n"));
		else if ((line[idx] == '>' || line[idx] == '<')
			&& manage_redir(cmd, line, &idx) == NO)
			return (NO);
		else if ((line[idx] == '$')
			&& manage_env(cmd, line, &idx) == NO)
			return (NO);
		else if (for_chunk(line[idx]) && manage_chunk(cmd, line, &idx) == NO)
			return (NO);
		if (is_whitespace(line[idx]) == YES)
			idx++;
	}
	g_exit_status = 0;
	return (YES);
}
