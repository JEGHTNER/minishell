/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:09:45 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/12 18:02:27 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_cmd *cmd, char **argv)
{
	char		path[1024];
	char		*new_path;

	if (cd_home_check(cmd, argv))
		return ;
	if (argv[1][0] == '/')
	{
		if (chdir(argv[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(argv[1]);
			g_exit_status = 1;
			return ;
		}
		check_a_path(path, cmd);
		return ;
	}
	if (check_r_path(path, cmd, argv, &new_path))
		return ;
	refresh_path(path, cmd, new_path);
}

void	print_export(t_cmd *cmd, char **argv)
{
	t_env_lst	*tmp;

	if (argv[1] == NULL)
	{
		tmp = cmd->env_head;
		sort_env(cmd);
		while (tmp)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
			{
				printf("=");
				printf("\"%s\"", tmp->value);
			}
			printf("\n");
			tmp = tmp->next;
		}
		g_exit_status = 0;
		return ;
	}
}

void	export_err(char **argv, int *i, int *fail_flag)
{
	if (argument_check(argv[*i]) == 0)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(argv[*i], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_exit_status = 1;
		*fail_flag = 1;
	}
}

void	export_loop(t_cmd *cmd, char **argv, int *i, int *fail_flag)
{
	t_env_lst	*find;
	char		**split;

	while (argv[++(*i)])
	{
		*fail_flag = 0;
		export_err(argv, i, fail_flag);
		if (*fail_flag == 1)
			continue ;
		split = ft_split_export(argv[*i], '=');
		find = find_env(cmd, split[0]);
		if (find == NULL)
			add_env_list(cmd, split[0], split[1]);
		else if (split[1])
		{
			free(find->key);
			free(find->value);
			find->key = ft_strdup(split[0]);
			find->value = ft_strdup(split[1]);
		}
		g_exit_status = 0;
		free_words(split);
	}
}

void	export(t_cmd *cmd, char **argv)
{
	int			i;
	int			fail_flag;

	i = 0;
	fail_flag = 0;
	print_export(cmd, argv);
	export_loop(cmd, argv, &i, &fail_flag);
	if (fail_flag == 1)
		g_exit_status = 1;
}
