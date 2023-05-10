/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 04:51:37 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/10 19:58:51 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *str)
{
	if (ft_strlen(str) == 4 && !ft_strncmp(str, "echo", 4))
		return (ECH);
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, "cd", 2))
		return (CD);
	else if (ft_strlen(str) == 3 && !ft_strncmp(str, "pwd", 3))
		return (PWD);
	else if (ft_strlen(str) == 6 && !ft_strncmp(str, "export", 6))
		return (EXPORT);
	else if (ft_strlen(str) == 5 && !ft_strncmp(str, "unset", 5))
		return (UNSET);
	else if (ft_strlen(str) == 3 && !ft_strncmp(str, "env", 3))
		return (ENV);
	else if (ft_strlen(str) == 4 && !ft_strncmp(str, "exit", 4))
		return (EXIT);
	return (NOT);
}

int	do_builtin(int is_builtin, t_token *node, t_cmd *cmd)
{
	if (is_builtin == ECH)
	{
		echo(node->argv);
		return (g_exit_status);
	}
	else if (is_builtin == CD)
	{
		cd(cmd, node->argv);
		return (g_exit_status);
	}
	else if (is_builtin == PWD)
	{
		pwd();
		return (g_exit_status);
	}
	else if (is_builtin == EXPORT)
	{
		export(cmd, node->argv);
		return (g_exit_status);
	}
	else
		return (do_builtin2(is_builtin, node, cmd));
}

int	do_builtin2(int is_builtin, t_token *node, t_cmd *cmd)
{
	int	ret;

	if (is_builtin == UNSET)
	{
		unset(cmd, node->argv);
		return (g_exit_status);
	}
	else if (is_builtin == ENV)
	{
		env(cmd);
		return (g_exit_status);
	}
	else if (is_builtin == EXIT)
	{
		ret = ft_exit(node->argv);
		if (ret == 0 || ret == 1)
			exit (g_exit_status);
		printf("exit\n");
	}
	return (NOT);
}
