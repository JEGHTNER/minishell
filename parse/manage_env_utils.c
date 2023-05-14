/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:37:38 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:13 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_macro	is_it_in_charset(char checker, char *charset)
{
	while (*charset)
	{
		if (checker == *charset)
			return (YES);
		charset++;
	}
	return (NO);
}

t_macro	is_it_env_key(char check)
{
	if (check && is_whitespace(check) == NO
		&& is_it_in_charset(check, "$./`~!#^&%%*(){}\\|\'\";?") == NO)
		return (YES);
	else
		return (NO);
}

void	add_env_list(t_cmd *cmd, char *for_key, char *for_value)
{
	t_env_lst	*to_put;
	t_env_lst	*cur;

	to_put = (t_env_lst *)malloc(sizeof(t_env_lst));
	if (!to_put)
		ft_exit_with_error("malloc error", 0);
	to_put->key = ft_strdup(for_key);
	to_put->value = ft_strdup(for_value);
	to_put->next = 0;
	to_put->prev = 0;
	if (cmd->env_head == 0)
		cmd->env_head = to_put;
	else
	{
		cur = cmd->env_head;
		while (cur->next)
			cur = cur->next;
		cur->next = to_put;
		to_put->prev = cur;
	}
}

void	init_env_lst(t_cmd *cmd, char **envp)
{
	size_t	idx;
	char	*key;
	char	*value;

	while (*envp)
	{
		idx = 0;
		while ((*envp)[idx] && (*envp)[idx] != '=')
			idx++;
		key = strchop(*envp, 0, idx - 1);
		value = strchop(*envp, idx + 1, ft_strlen(*envp) - 1);
		add_env_list(cmd, key, value);
		free(key);
		free(value);
		envp++;
	}
}

char	*find_value_with_key(t_env_lst *head, char *to_find)
{
	t_env_lst	*cur;

	cur = head;
	while (cur)
	{
		if (ft_strncmp(cur->key, to_find, ft_strlen(cur->key) + 1) == 0)
			return (ft_strdup(cur->value));
		cur = cur->next;
	}
	return (ft_strdup(""));
}
