/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:02:23 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/06 20:36:30 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"
#include <string.h>

int	status;

void	echo(char *str)
{
	printf("%s%%", str);
}

void	env(char **my_env)
{
	char	**tmp;

	tmp = my_env;
	while (*tmp)
	{
		printf("%s\n", *tmp);
		tmp++;
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

char	**cpy_env(char **envp)
{
	char	**tmp;
	char	**my_env;
	int		env_cnt;
	int		i;

	tmp = envp;
	env_cnt = 0;
	while (*tmp)
	{
		env_cnt++;
		tmp++;
	}
	my_env = malloc(sizeof(char *) * (env_cnt + 1));
	i = -1;
	while (++i < env_cnt)
		my_env[i] = strdup(envp[i]);
	my_env[i] = NULL;
	return (my_env);
}

int	main(int ac, char **av, char **envp)
{
	// char	*value;
	char	**my_env;

	if (ac)
		;
	if (av)
		;
	my_env = cpy_env(envp);
	echo("string test");
	pwd();
	// env(my_env);
	return 0;
}
