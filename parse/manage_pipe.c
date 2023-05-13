/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:24:06 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/10 20:05:21 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_macro	manage_pipe(t_cmd *cmd, char *line, size_t *idx)
{
	if (cmd->chunk_head == 0)
		return (error_n_ret("syntax error near unexpected token\n"));
	else
	{
		if (line[*idx + 1] == '|')
			return (error_n_ret("syntax error near unexpected token\n"));
		if (line[*idx + 1] == '\0')
			return (error_n_ret("syntax error\n"));
		insert_node(ft_strdup("|"), cmd, PIPE);
		(*idx)++;
	}
	return (YES);
}
