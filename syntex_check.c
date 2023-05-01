/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntex_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:01:49 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/27 13:01:51 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	pipe_syntax_check(t_element *cur)
{
	if (cur->next->c_flag == WORD)
		return ;
	else
		ft_exit_with_error("token syntex error : ", "pipe");
}

static void	redir_syntax_check(t_element *cur)
{
	if (cur->next->c_flag == WORD)
		return ;
	else
		ft_exit_with_error("token syntex error : ", "io_redirection");
}

// void	word_syntax_check(t_element *cur)
// {
// }

void	syntex_check(t_cmd *cmd)
{
	t_element	*cur;

	cur = cmd->chunk_head;
	while (cur)
	{
		if (cur->c_flag == REDIR)
			redir_syntax_check(cur);
		else if (cur->c_flag == PIPE)
			pipe_syntax_check(cur);
		cur = cur->next;
	}
}
