/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:02:23 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/11 20:48:43 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"
#include <string.h>

int	argument_check(char *string);
t_list	*find_env(t_list **my_env, char *string);

long long	exit_status = 0;

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

void	check_exit_arguments(char **arguments)
{
	char	*tmp;
	int		cnt;

	tmp = *arguments;
	cnt = 0;
	while (tmp)
	{
		cnt++;
		if (!check_isdigit(tmp))
		{
			exit_status = 255;
			break ;
		}
		tmp++;
	}
	if (cnt > 1)
	{
		exit_status = 1;
		printf("minishell: exit: too many arguments\n");
	}
	if (exit_status == 255)
		printf("minishell: exit: %s: numeric argument required\n", tmp);
}

void	ft_exit(char **arguments)
{
	if (arguments == NULL)
		exit(0);
	if (*arguments == NULL)
		exit(0);
	check_exit_arguments(arguments);
}

void	echo(char *str, int option)
{
	if (option == 0)
		printf("%s\n", str);
	else
		printf("%s%%", str);
	exit_status = 0;
}

void	env(t_list **my_env)
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

void	del_env(t_list **my_env, t_list *find)
{
	if (find == NULL)
		return ;
	if (find == *my_env)
	{
		*my_env = find->next;
		if (*my_env)
			(*my_env)->prev = NULL;
		free(find->content);
		free(find);
		return ;
	}
	find->prev->next = find->next;
	if (find->next)
		find->next->prev = find->prev;
	free(find->content);
	free(find);
	return ;
}

void	unset(t_list **my_env, char *string)
{
	t_list	*find;

	if (string == NULL)
		return ;
	if (argument_check(string) == 0)
	{
		printf("unset: '%s': not a valid identifier\n", string);
		exit_status = 1;
	}
	find = find_env(my_env, string);
	if (find == NULL)
		return ;
	del_env(my_env, find);
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

int	argument_check(char *string)
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
	t_list	**my_env;

	if (ac)
		;
	if (av)
		;
	my_env = malloc(sizeof(t_list *));
	if (!my_env)
		return (1);
	cpy_env(my_env, envp);
	// echo("string test", 0);
	// env(my_env);
	cd(my_env, "src");
	pwd();
	// export(my_env, NULL);
	// env(my_env);
	// unset(my_env, "test1");
	cd(my_env, "..");
	pwd();
	env(my_env);
	char extest[1] = {"a"};
	ft_exit(extest);
	return 0;
}
