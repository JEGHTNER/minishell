/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:04:58 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/10 20:16:00 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **arguments)
{
	if (arguments == NULL)
		exit(g_exit_status);
	if (arguments[1] == NULL)
		exit(g_exit_status);
	return (check_exit_arguments(arguments));
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
	int			fail_flag;

	if (argv == NULL)
		return ;
	i = 0;
	fail_flag = 0;
	while (argv[++i])
	{
		if (argument_check(argv[i]) == 0)
		{
			printf("unset: '%s': not a valid identifier\n", argv[i]);
			fail_flag = 1;
			continue ;
		}
		find = find_env(cmd, argv[i]);
		if (find == NULL)
			continue ;
		del_env(cmd, find);
	}
	if (fail_flag == 1)
		g_exit_status = 1;
	else
		g_exit_status = 0;
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
