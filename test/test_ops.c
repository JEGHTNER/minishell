/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:15:49 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/11 16:16:04 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_element *head)
{
	size_t	idx = 1;

	while (head)
	{
		printf("list no.%zu\t:\t%s\n", idx, head->content);
		head = head->next;
		idx++;
	}
}

void	print_env(t_env_lst *head)
{
	while (head)
	{
		printf("key: %s\n", head->key);
		printf("value: %s\n\n", head->value);
		head = head->next;
	}
}

void	print_tree(t_token *head)
{
	if (head == 0)
		return ;
	print_tree(head->left);
	printf("type: %d", head->cat);
	if (head->argc >= 1)
		for (int i = 0; i < head->argc; i++)
			printf(" %s ", head->argv[i]);
	printf("\n");
	print_tree(head->right);
}
