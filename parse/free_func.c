/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:15:33 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 22:28:20 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_cmd *cmd, char *line)
{
	free(line);
	if (g_exit_status != 258)
	{
		if (cmd->chunk_head)
			ft_free_list(&(cmd->chunk_head));
		if (cmd->tree_head)
			ft_free_tree(&(cmd->tree_head));
	}
	else
	{
		if (cmd->chunk_head)
			ft_free_list_err(&(cmd->chunk_head));
	}
}

void	ft_free_tree(t_token **head)
{
	size_t	idx;

	idx = 0;
	if ((*head)->left)
		ft_free_tree(&((*head)->left));
	if ((*head)->right)
		ft_free_tree(&((*head)->right));
	if ((*head)->argc != 0)
	{
		while (idx < (size_t)((*head)->argc))
			free(((*head)->argv)[idx++]);
		free((*head)->argv);
	}
	if ((*head)->cat == CMD)
	{
		free((*head)->fail_flag);
		free((*head)->redirect_flag);
		free((*head)->is_hd);
	}
	if ((*head)->cat == PIPE)
		free((*head)->pipe_fd);
	free(*head);
	*head = 0;
}

void	ft_free_list(t_element **head)
{
	t_element	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
	head = 0;
}

void	ft_free_list_err(t_element **head)
{
	t_element	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = tmp;
	}
	head = 0;
}
