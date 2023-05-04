/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:12:07 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/04 13:22:42 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;

	tmp = *arguments;
	cnt = 0;
	i = 0;
	while (tmp[i])
	{
		cnt++;
		if (!check_isdigit(tmp))
		{
			exit_status = 255;
			break ;
		}
		i++;
	}
	if (cnt > 1)
	{
		exit_status = 1;
		printf("minishell: exit: too many arguments\n");
		exit(1);
	}
	if (exit_status == 255)
	{
		printf("minishell: exit: %s: numeric argument required\n", tmp);
		exit(255);
	}
}
