/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:37:38 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/08 22:31:29 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_tree(t_token *node, t_cmd *cmd)
{
	// char *cat[6] = {"WORD", "CMD", "SIMPLE_CMD", "REDIRS", "REDIR", "PIPE"};
	// printf("node->cat: %s\n", cat[node->cat]);
	// if (node->argv)
	// 	printf("node->argv[0]: %s\n", node->argv[0]);
	// else
	// 	printf("node->argv: NULL\n");
	// if (node->left)
	// 	printf("node->left->cat: %s\n", cat[node->left->cat]);
	// else
	// 	printf("node->left: NULL\n");
	// if (node->right)
	// 	printf("node->right->cat: %s\n", cat[node->right->cat]);
	// else
	// 	printf("node->right: NULL\n");

	execute_tree(node, cmd);
	if (node->left != NULL)
		search_tree(node->left, cmd);
	if (node->right != NULL)
		search_tree(node->right, cmd);
}

void	search_hd(t_token *node, int *hd_cnt)
{
	if (node->cat == REDIR)
	{
		if (ft_strncmp(node->argv[0], "<<", 2) == 0)
		{
			here_doc_tmp(node->argv[1], *hd_cnt);
			node->hd_index = *hd_cnt;
			*hd_cnt += 1;
		}
	}
	if (node->left != NULL)
		search_hd(node->left, hd_cnt);
	if (node->right != NULL)
		search_hd(node->right, hd_cnt);
}

int	execute_tree(t_token *node, t_cmd *cmd)
{
	if (node->cat == PIPE)
		exec_pipe(node);
	else if (node->cat == REDIRS)
		exec_redirs(node);
	else if (node->cat == REDIR)
		exec_redir(node);
	else if (node->cat == CMD)
		exec_cmd(node);
	else if (node->cat == SIMPLE_CMD)
		exec_scmd(node, cmd);
	return (0);
}
