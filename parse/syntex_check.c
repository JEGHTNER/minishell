/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntex_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:01:49 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:22 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_macro	pipe_syntax_check(t_element *cur)
{
	if (cur->next != 0)
		return (YES);
	else
		return (error_n_ret("syntax error near unexpected token"));
}

static t_macro	redir_syntax_check(t_element *cur)
{
	if (cur->next->c_flag == WORD)
		return (YES);
	else
		return (error_n_ret("syntax error near unexpected token"));
}

t_macro	syntex_check(t_cmd *cmd)
{
	t_element	*cur;

	cur = cmd->chunk_head;
	while (cur)
	{
		if (cur->c_flag == REDIR)
		{
			if (redir_syntax_check(cur) == NO)
				return (NO);
		}
		else if (cur->c_flag == PIPE)
		{
			if (pipe_syntax_check(cur) == NO)
				return (NO);
		}
		cur = cur->next;
	}
	return (YES);
}
