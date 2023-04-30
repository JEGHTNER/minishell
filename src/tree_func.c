/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:37:38 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/30 17:21:06 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell_jehelee.h"

void	search_tree(t_token *node, t_list **my_env)
{
	// printf("node->cat: %d\n", node->cat);
	execute_tree(node, my_env);
	if (node->left != NULL)
		search_tree(node->left, my_env);
	if (node->right != NULL)
		search_tree(node->right, my_env);
}

void	search_hd(t_token *node, t_list **my_env, int *hd_cnt)
{
	if (node->cat == REDIR)
	{
		if (node->argv[0] == "<<")
		{
			printf("%s %s %d\n", node->argv[0], node->argv[1], *hd_cnt);
			here_doc_tmp(node->argv[1], *hd_cnt);
			node->hd_index = *hd_cnt;
			*hd_cnt += 1;
		}
	}
	if (node->left != NULL)
		search_hd(node->left, my_env, hd_cnt);
	if (node->right != NULL)
		search_hd(node->right, my_env, hd_cnt);
}

int	execute_tree(t_token *node, t_list **my_env)
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
		exec_scmd(node, my_env);
}
