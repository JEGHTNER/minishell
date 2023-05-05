/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:09:45 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/05 19:03:57 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_list **my_env, char **argv)
{
	char	path[1024];
	char	*new_path;
	char	*tmp;
	t_list	*old_pwd;
	t_list	*pwd;

	// if (!argv[1])
	// {
	// 	if (chdir(find_env(my_env, "HOME")->content + 5) == -1)
	// 	{
	// 		exit_status = 1;
	// 		printf("minishell: cd: HOME not set\n");
	// 	}
	// 	exit_status = 0;
	// 	return ;
	// }
	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	pwd = find_env(my_env, "PWD");
	old_pwd = find_env(my_env, "OLDPWD");
	if (old_pwd == NULL)
		ft_lstadd_back(my_env, ft_lstnew("OLDPWD="));
	free(old_pwd->content);
	old_pwd ->content = ft_strjoin("OLD", pwd->content);
	tmp = ft_strjoin(path, "/");
	new_path = ft_strjoin(tmp, argv[1]);
	free(tmp);
	if (access(new_path, F_OK) == -1)
	{
		exit_status = 1;
		printf("minishell: cd: %s: No such file or directory", argv[1]);
		return ;
	}
	pwd->content = ft_strjoin("PWD=", new_path);
	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	pwd->content = ft_strjoin("PWD=", path);
	chdir(new_path);
	free(new_path);
	exit_status = 0;
}

// void	export(t_list **my_env, char **argv)
// {
// 	t_list	*find;
// 	t_list	*tmp;
// 	char	**split;
// 	int		i;
// 	int		fail_flag;

// 	fail_flag = 0;
// 	if (argv[1] == NULL)
// 	{
// 		tmp = *my_env;
// 		sort_env(my_env);
// 		while (tmp)
// 		{
// 			printf("declare -x %s\n", (char *)tmp->content);
// 			tmp = tmp->next;
// 		}
// 		exit_status = 0;
// 		return ;
// 	}
// 	i = 0;
// 	while (argv[++i])
// 	{
// 		if (argument_check(argv[i]) == 0)
// 		{
// 			printf("export: '%s': not a valid identifier\n", argv[i]);
// 			exit_status = 1;
// 			fail_flag = 1;
// 		}
// 		if (fail_flag == 1)
// 			continue ;
// 		split = ft_split(argv[i], '=');
// 		find = find_env(my_env, split[0]);
// 		if (find == NULL)
// 			ft_lstadd_back(my_env, ft_lstnew(argv[i]));
// 		else
// 		{
// 			free(find->content);
// 			find->content = ft_strdup(argv[i]);
// 		}
// 		exit_status = 0;
// 	}
// 	if (fail_flag == 1)
// 		exit_status = 1;
// }

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
		// sort_env(cmd);
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
	}
	if (fail_flag == 1)
		exit_status = 1;
}
