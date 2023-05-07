/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:04:58 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/08 05:01:56 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **arguments)
{
	if (arguments == NULL)
	{
		g_exit_status = 0;
		return ;
	}
	if (arguments[1] == NULL)
	{
		g_exit_status = 0;
		return ;
	}
	check_exit_arguments(arguments);
}

void	echo(char **argv)
{
	int		i;
	int		option;

	option = get_echo_option(argv[1]);
	if (option == 0)
	{
		i = 0;
		while (argv[++i])
		{
			if (i > 1)
				printf(" %s", argv[i]);
			else
				printf("%s", argv[i]);
		}
		printf("\n");
	}
	else
		echo_n(argv);
	g_exit_status = 0;
}

void	env(t_cmd *cmd)
{
	t_env_lst	*tmp;

	tmp = cmd->env_head;
	while (tmp)
	{
		if (tmp->value)
		{
			printf("%s", tmp->key);
			printf("=");
			printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
	g_exit_status = 0;
}

void	unset(t_cmd *cmd, char **argv)
{
	t_env_lst	*find;
	int			i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[++i])
	{
		if (argument_check(argv[i]) == 0)
		{
			printf("unset: '%s': not a valid identifier\n", argv[i]);
			g_exit_status = 1;
		}
		find = find_env(cmd, argv[i]);
		if (find == NULL)
			g_exit_status = 0;
		del_env(cmd, find);
		g_exit_status = 0;
	}
}

void	pwd(void)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	printf("%s\n", path);
	g_exit_status = 0;
	return ;
}
