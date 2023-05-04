/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:04:58 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/04 13:21:28 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **arguments)
{
	if (arguments == NULL)
		exit(0);
	if (*arguments == NULL)
		exit(0);
	check_exit_arguments(arguments);
}

void	echo(char **argv, int option)
{
	int		i;

	if (option == 0)
	{
		i = 0;
		while (argv[++i])
			printf("%s\n", argv[i]);
	}
	else
	{
		i = 0;
		while (argv[++i])
			printf("%s%%", argv[i]);
	}
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

void	unset(t_list **my_env, char **argv)
{
	t_list	*find;
	int		i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[++i])
	{
		if (argument_check(argv[i]) == 0)
		{
			printf("unset: '%s': not a valid identifier\n", argv[i]);
			exit_status = 1;
		}
		find = find_env(my_env, argv[i]);
		if (find == NULL)
			exit(0);
		del_env(my_env, find);
		exit_status = 0;
	}
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
