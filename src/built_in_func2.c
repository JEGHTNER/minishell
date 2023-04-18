/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulit_in_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:09:45 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/16 14:10:18 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"

extern long long	exit_status;

void	cd(t_list **my_env, char *go_path)
{
	char	path[1024];
	char	*new_path;
	char	*tmp;
	t_list	*old_pwd;
	t_list	*pwd;

	if (my_env)
		;
	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	pwd = find_env(my_env, "PWD");
	old_pwd = find_env(my_env, "OLDPWD");
	if (old_pwd == NULL)
		ft_lstadd_back(my_env, ft_lstnew("OLDPWD="));
	free(old_pwd->content);
	old_pwd ->content = ft_strjoin("OLD", pwd->content);
	tmp = ft_strjoin(path, "/");
	new_path = ft_strjoin(tmp, go_path);
	free(tmp);
	if (access(new_path, F_OK) == -1)
	{
		exit_status = 1;
		printf("bash: cd: %s: No such file or directory", go_path);
	}
	pwd->content = ft_strjoin("PWD=", new_path);
	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	pwd->content = ft_strjoin("PWD=", path);
	chdir(new_path);
	free(new_path);
	exit_status = 0;
}

void	export(t_list **my_env, char *string)
{
	t_list	*find;
	t_list	*tmp;
	char	**split;

	if (string == NULL)
	{
		tmp = *my_env;
		sort_env(my_env);
		while (tmp)
		{
			printf("declare -x %s\n", tmp->content);
			tmp = tmp->next;
		}
		exit_status = 0;
		return ;
	}
	if (argument_check(string) == 0)
	{
		printf("export: '%s': not a valid identifier\n", string);
		exit_status = 1;
		return ;
	}
	split = ft_split(string, '=');
	// printf("%s", split[0]);
	find = find_env(my_env, split[0]);
	if (find == NULL)
		ft_lstadd_back(my_env, ft_lstnew(string));
	else
	{
		free(find->content);
		find->content = ft_strdup(string);
	}
	exit_status = 0;
}
