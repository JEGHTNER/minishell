/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:12:07 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/09 18:11:40 by jehelee          ###   ########.fr       */
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
	if (ft_isalpha(string[0]) == 0 && string[0] != '_')
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

int	check_exit_arguments_err(int cnt, char *argument)
{
	if (cnt > 1)
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (2);
	}
	if (g_exit_status == 255)
	{
		g_exit_status = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argument, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (1);
	}
	return (0);
}

int	check_exit_arguments(char **arguments)
{
	int		cnt;
	int		i;
	int		ret;

	cnt = 0;
	i = 0;
	while (arguments[++i])
	{
		cnt++;
		if (!check_isdigit(arguments[i]))
		{
			g_exit_status = 255;
			break ;
		}
	}
	ret = check_exit_arguments_err(cnt, arguments[i]);
	if (!ret)
	{
		g_exit_status = ft_atoi(arguments[1]);
		return (0);
	}
	return (ret);
}
