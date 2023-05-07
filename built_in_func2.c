/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:09:45 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/08 04:08:21 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home_check(t_cmd *cmd, char **argv)
{
	if (!argv[1])
	{
		if (chdir(find_value_with_key(cmd->env_head, "HOME")) == -1)
		{
			exit_status = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		}
		return (1);
	}
	return (0);
}

void	refresh_path(char *path, t_cmd *cmd, char *new_path)
{
	t_env_lst	*old_pwd;
	t_env_lst	*pwd;

	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	pwd = find_env(cmd, "PWD");
	old_pwd = find_env(cmd, "OLDPWD");
	free(pwd->value);
	pwd->value = ft_strdup(path);
	chdir(new_path);
	free(new_path);
	exit_status = 0;
}

void	check_a_path(char *path, t_cmd *cmd)
{
	t_env_lst	*old_pwd;
	t_env_lst	*pwd;

	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	pwd = find_env(cmd, "PWD");
	old_pwd = find_env(cmd, "OLDPWD");
	if (old_pwd == NULL)
		add_env_list(cmd, pwd->key, pwd->value);
	free(old_pwd->value);
	old_pwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = ft_strdup(path);
	exit_status = 0;
	return ;
}

int	check_r_path(char *path, t_cmd *cmd, char **argv, char *new_path)
{
	char		*tmp;
	t_env_lst	*old_pwd;
	t_env_lst	*pwd;

	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	pwd = find_env(cmd, "PWD");
	old_pwd = find_env(cmd, "OLDPWD");
	if (old_pwd == NULL)
		add_env_list(cmd, pwd->key, pwd->value);
	free(old_pwd->value);
	old_pwd->value = ft_strdup(pwd->value);
	tmp = ft_strjoin(path, "/");
	new_path = ft_strjoin(tmp, argv[1]);
	free(tmp);
	if (chdir(new_path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(argv[1]);
		exit_status = 1;
		return (1);
	}
	free(pwd->value);
	pwd->value = ft_strdup(new_path);
	return (0);
}

void	cd(t_cmd *cmd, char **argv)
{
	char		path[1024];
	char		*new_path;
	char		*tmp;
	t_env_lst	*old_pwd;
	t_env_lst	*pwd;

	if (cd_home_check(cmd, argv))
		return ;
	if (argv[1][0] == '/')
	{
		if (chdir(argv[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(argv[1]);
			exit_status = 1;
			return ;
		}
		check_a_path(path, cmd);
		return ;
	}
	if (check_r_path(path, cmd, argv, new_path))
		return ;
	refresh_path(path, cmd, new_path);
}

void	export(t_cmd *cmd, char **argv)
{
	t_env_lst	*find;
	t_env_lst	*tmp;
	char		**split;
	int			i;
	int			fail_flag;

	fail_flag = 0;
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
		exit_status = 0;
		return ;
	}
	i = 0;
	while (argv[++i])
	{
		if (argument_check(argv[i]) == 0)
		{
			printf("export: '%s': not a valid identifier\n", argv[i]);
			exit_status = 1;
			fail_flag = 1;
		}
		if (fail_flag == 1)
			continue ;
		split = ft_split_export(argv[i], '=');
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
		exit_status = 0;
		free_words(split);
	}
	if (fail_flag == 1)
		exit_status = 1;
}
