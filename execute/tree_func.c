/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:37:38 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/14 23:10:52 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_tree(t_token *node, t_cmd *cmd)
{
	execute_tree(node, cmd);
	if (node->left != NULL)
		search_tree(node->left, cmd);
	if (node->right != NULL)
		search_tree(node->right, cmd);
}

void	search_hd(t_cmd *cmd, t_token *node, int *hd_cnt, int *hd_fail)
{
	if (node->cat == REDIR)
	{
		if (ft_strncmp(node->argv[0], "<<", 2) == 0)
		{
			here_doc_tmp(cmd, node->argv[1], *hd_cnt, hd_fail);
			node->hd_index = *hd_cnt;
			*hd_cnt += 1;
		}
	}
	if (node->left != NULL)
		search_hd(cmd, node->left, hd_cnt, hd_fail);
	if (node->right != NULL)
		search_hd(cmd, node->right, hd_cnt, hd_fail);
}

int	execute_tree(t_token *node, t_cmd *cmd)
{
	if (node->cat == PIPE)
		exec_pipe(node);
	else if (node->cat == REDIRS)
		exec_redirs(node);
	else if (node->cat == REDIR)
		exec_redir(node, cmd);
	else if (node->cat == CMD)
		exec_cmd(node);
	else if (node->cat == SIMPLE_CMD)
		exec_scmd(node, cmd);
	return (0);
}
