/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:04:58 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/05 19:06:28 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **arguments)
{
	if (arguments == NULL)
	{
		exit_status = 0;
		return ;
	}
	if (arguments[1] == NULL)
	{
		exit_status = 0;
		return ;
	}
	check_exit_arguments(arguments);
}

int	get_echo_option(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	echo(char **argv)
{
	int		i;
	int		option;

	option = get_echo_option(argv[1]);
	if (option == 0)
	{
		i = 0;
		while (argv[++i])
		{
			if (i > 1)
				printf(" %s", argv[i]);
			else
				printf("%s", argv[i]);
		}
		printf("\n");
	}
	else
	{
		i = 1;
		while (argv[++i])
		{
			if (i > 2)
				printf(" %s", argv[i]);
			else
				printf("%s", argv[i]);
		}
	}
	exit_status = 0;
}

void	env(t_cmd *cmd)
{
	t_env_lst	*tmp;

	tmp = cmd->env_head;
	while (tmp)
	{
		if (tmp->value)
		{
			printf("%s", tmp->key);
			printf("=");
			printf("%s\n", tmp->value);
		}
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
			exit_status = 0;
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
