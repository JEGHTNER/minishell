/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:22:56 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/23 12:22:57 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	convert_tree(t_cmd *cmd)
{
	t_element   *cur;
	t_token     *to_put;

	cur = cmd->chunk_head;
	while (cur)
	{
		to_put = change_element_token(&cur);
		put_in_tree(cmd, to_put);
	}
}
