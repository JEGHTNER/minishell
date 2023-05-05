/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:12:07 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/05 19:59:28 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*find_env(t_cmd *cmd, char *string)
{
	t_env_lst	*tmp;

	tmp = cmd->env_head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, string, ft_strlen(string)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	argument_check(char *string)
{
	int	i;

	i = 0;
	if (ft_isalpha(string[0])== 0 && string[0] != '_')
		return (0);
	while (string[i])
	{
		if (string[i] == '=')
			return (1);
		if (ft_isalnum(string[i]) == 0 && string[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void sort_env(t_cmd *cmd)
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

int	check_isdigit(char *string)
{
	if (string == NULL)
		return (1);
	while (*string)
	{
		if (!ft_isdigit(*string))
			return (0);
		string++;
	}
	return (1);
}

void	check_exit_arguments(char **arguments)
{
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	while (arguments[++i])
	{
		cnt++;
		if (!check_isdigit(arguments[i]))
		{
			exit_status = 255;
			break ;
		}
	}
	if (cnt > 1)
	{
		exit_status = 1;
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	if (exit_status == 255)
	{
		exit_status = 255;
		printf("minishell: exit: numeric argument required\n");
		return ;
	}
	exit_status = ft_atoi(arguments[1]);
}
