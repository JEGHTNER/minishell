/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:04:58 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/16 14:09:29 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"

extern long long	exit_status;

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
