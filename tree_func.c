/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:37:38 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/05 16:46:13 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	search_tree(t_token *node, t_list **my_env)
// {
// 	execute_tree(node, my_env);
// 	if (node->left != NULL)
// 		search_tree(node->left, my_env);
// 	if (node->right != NULL)
// 		search_tree(node->right, my_env);
// }

void	search_tree(t_token *node, t_cmd *cmd)
{
	execute_tree(node, cmd);
	if (node->left != NULL)
		search_tree(node->left, cmd);
	if (node->right != NULL)
		search_tree(node->right, cmd);
}

void	search_hd(t_token *node, t_list **my_env, int *hd_cnt)
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
		search_hd(node->left, my_env, hd_cnt);
	if (node->right != NULL)
		search_hd(node->right, my_env, hd_cnt);
}

// int	execute_tree(t_token *node, t_list **my_env)
// {
// 	if (node->cat == PIPE)
// 		exec_pipe(node);
// 	else if (node->cat == REDIRS)
// 		exec_redirs(node);
// 	else if (node->cat == REDIR)
// 		exec_redir(node);
// 	else if (node->cat == CMD)
// 		exec_cmd(node);
// 	else if (node->cat == SIMPLE_CMD)
// 		exec_scmd(node, my_env);
// 	return (0);
// }

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
