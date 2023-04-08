/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:02:23 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/08 21:43:22 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"
#include <string.h>

int	exit_status = 0;

void	echo(char *str, int option)
{
	if (option == 0)
		printf("%s\n", str);
	else
		printf("%s%%", str);
	exit_status = 0;
}

void	env(char **my_env)
{
	t_list	*tmp;

	tmp = *my_env;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	exit_status = 0;
}

void	pwd(void)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	printf("%s\n", path);
	exit_status = 0;
	return ;
}

void	cd(char **my_env, char *go_path)
{
	char	path[1024];
	char	*new_path;
	char	*tmp;

	if (my_env)
		;
	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	tmp = ft_strjoin(path, "/");
	new_path = ft_strjoin(tmp, go_path);
	chdir(new_path);
	printf("%s\n", new_path);
}

t_list	*find_env(t_list **my_env, char *string)
{
	t_list	*tmp;

	tmp = *my_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, string, ft_strlen(string)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	export_argument_check(char *string)
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

void sort_env(t_list **my_env)
{
	t_list	*tmp;
	t_list	*tmp2;
	char	*tmp_str;

	tmp = *my_env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->content, tmp2->content, ft_strlen(tmp->content)) > 0)
			{
				tmp_str = tmp->content;
				tmp->content = tmp2->content;
				tmp2->content = tmp_str;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
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
	if (export_argument_check(string) == 0)
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

void	cpy_env(t_list **my_env, char **envp)
{
	char	**tmp;
	int		env_cnt;
	int		i;

	tmp = envp;
	env_cnt = 0;
	while (*tmp)
	{
		env_cnt++;
		tmp++;
	}
	i = -1;
	while (++i < env_cnt)
		ft_lstadd_back(my_env, ft_lstnew(envp[i]));
	return ;
}

int	main(int ac, char **av, char **envp)
{
	// char	*value;
	t_env_lst	**my_env;

	if (ac)
		;
	if (av)
		;
	my_env = malloc(sizeof(t_list *));
	if (!my_env)
		return (1);
	cpy_env(my_env, envp);
	echo("string test", 0);
	// pwd();
	cd(my_env, "..");
	export(my_env, NULL);
	env(my_env);
	return 0;
}
