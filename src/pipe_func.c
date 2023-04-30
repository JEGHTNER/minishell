/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:41:10 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/24 18:41:30 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"

char	*get_path(char *cmd, char **path_args)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	if (!cmd || !path_args)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (path_args[i])
	{
		tmp = ft_strjoin(path_args[i], "/");
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, X_OK) == 0)
			return (tmp2);
		free(tmp2);
		i++;
	}
	return (NULL);
}

char	**get_path_args(t_list **my_env)
{
	int		i;
	char	*path;
	char	*new_envp;
	t_list	*tmp;

	i = 0;
	tmp = *my_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "PATH=", 5) == 0)
		{
			path = tmp->content + 5;
			return (ft_split(path, ':'));
		}
		tmp = tmp->next;
	}
	return (NULL);
}
