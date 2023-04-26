/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:37:38 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/26 18:37:39 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	rm_env_list(t_cmd *cmd, char *key)
{
	t_macro		flag;
	t_env_lst	*cur;
	t_env_lst	*tmp;

	flag = NO;
	cur = cmd->env_head;
	if (cur == 0)
		return ;
	while (cur->next)
	{
		if (ft_strncmp(key, cur->next->key, ft_strlen(key)) == 0)
		{
			flag = YES;
			break ;
		}
		cur = cur->next;
	}
	if (flag == YES)
	{
		tmp = cur->next;
		tmp->next = cur->next->next;
		free(tmp);
	}
}

void    add_env_list(t_cmd *cmd, char *key, char *value)
{
	t_env_lst   *to_put;
	t_env_lst   *cur;

	to_put = (t_env_lst *)malloc(sizeof(t_env_lst));
	if (!to_put)
		ft_exit_with_error("malloc error", 0);
	to_put->key = key;
	to_put->value = value;
	to_put->next = 0;
	if (cmd->env_head == 0)
		cmd->env_head = to_put;
	else
	{
		cur = cmd->env_head;
		while (cur->next)
			cur = cur->next;
		cur->next = to_put;
	}
}

void    init_env_lst(t_cmd *cmd, char **envp)
{
	size_t  idx;
	char    *key;
	char    *value;

	while (*envp)
	{
		idx = 0;
		while (*envp[idx] != '=')
			idx++;
		key = strchop(*envp, 0, idx - 1);
		if (!key)
			ft_exit_with_error("malloc error", 0);
		value = strchop(*envp, idx + 1, ft_strlen(*envp));
		if (!value)
			ft_exit_with_error("malloc error", 0);
		add_env_list(cmd, key, value);
		(*envp)++;
	}
}

char    *find_value_with_key(t_env_lst *head, char *to_find)
{
	t_env_lst   *cur;

	cur = head;
	while (cur)
	{
		if (ft_strncmp(cur->key, to_find, ft_strlen(cur->key) + 1) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (0);
}