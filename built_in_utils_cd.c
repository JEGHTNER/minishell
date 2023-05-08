/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils_cd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 04:27:34 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/08 05:01:57 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home_check(t_cmd *cmd, char **argv)
{
	if (!argv[1])
	{
		if (chdir(find_value_with_key(cmd->env_head, "HOME")) == -1)
		{
			g_exit_status = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		}
		g_exit_status = 0;
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
	g_exit_status = 0;
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
	g_exit_status = 0;
	return ;
}

int	check_r_path(char *path, t_cmd *cmd, char **argv, char **new_path)
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
	*new_path = ft_strjoin(tmp, argv[1]);
	free(tmp);
	if (chdir(*new_path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(argv[1]);
		g_exit_status = 1;
		return (1);
	}
	free(pwd->value);
	pwd->value = ft_strdup(*new_path);
	return (0);
}
