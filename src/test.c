/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:02:23 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/07 21:07:20 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"
#include <string.h>

int	status;

void	echo(char *str, int option)
{
	if (option == 0)
		printf("%s\n", str);
	else
		printf("%s%%", str);
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
}

void	pwd(void)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	printf("%s\n", path);
	return ;
}

void	cd(char **my_env, char *go_path)
{
	char	path[1024];
	char	*new_path;
	char	*tmp;

	if( my_env)
		;
	if (getcwd(path, 1024) == NULL)
		perror("getcwd error\n");
	tmp = ft_strjoin(path, "/");
	new_path = ft_strjoin(tmp, go_path);
	chdir(new_path);
	printf("%s\n", new_path);
}

void	export(char **my_env, char *string)
{
	if (string == NULL)
	{
		env(my_env);
	}
	
}

void	cpy_env(t_list *my_env, char **envp)
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
	{
		t_list *envp_i = ft_lstnew(envp[i]);
		ft_lstadd_back(&my_env, envp_i);
	}
	return ;
}

int	main(int ac, char **av, char **envp)
{
	// char	*value;
	t_env_lst	*my_env;

	if (ac)
		;
	if (av)
		;
	my_env = malloc(sizeof(t_list *));
	if (!my_env)
		return(1);
	cpy_env(my_env, envp);
	echo("string test", 0);
	// pwd();
	env(my_env);
	cd(my_env,"src"); 
	return 0;
}
