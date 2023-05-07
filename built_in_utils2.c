/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:15:09 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/08 05:02:00 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(t_cmd *cmd, t_env_lst *find)
{
	if (find == NULL)
		return ;
	if (find == cmd->env_head)
	{
		cmd->env_head = find->next;
		free(find->key);
		free(find->value);
		free(find);
		return ;
	}
	find->prev->next = find->next;
	if (find->next)
		find->next->prev = find->prev;
	free(find->key);
	free(find->value);
	free(find);
	return ;
}

int	get_echo_option(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	echo_n(char **argv)
{
	int		i;
	int		option;

	i = 1;
	while (argv[++i])
	{
		if (i > 2)
			printf(" %s", argv[i]);
		else
			printf("%s", argv[i]);
	}
}

void	sort_env(t_cmd *cmd)
{
	t_env_lst	*tmp;
	t_env_lst	*tmp2;
	char		*tmp_key;
	char		*tmp_val;

	tmp = cmd->env_head;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->key, tmp2->key, ft_strlen(tmp->key)) > 0)
			{
				tmp_key = tmp->key;
				tmp->key = tmp2->key;
				tmp2->key = tmp_key;
				tmp_val = tmp->value;
				tmp->value = tmp2->value;
				tmp2->value = tmp_val;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
