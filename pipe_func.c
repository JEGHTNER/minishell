/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:41:10 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/07 22:50:31 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd, char **path_args)
{
	int			i;
	char		*tmp;
	char		*tmp2;
	DIR			*is_dir;

	if (!cmd)
		return (NULL);
	is_dir = opendir(cmd);
	if (is_dir != NULL)
	{
		if (ft_strchr(cmd, '/') != NULL)
		{
			printf("minishell: %s: is a directory\n", cmd);
			exit(126);
		}
		return (NULL);
	}
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	if (!path_args)
		return (NULL);
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

char	**get_path_args(t_cmd *cmd)
{
	int			i;
	char		*path;
	t_env_lst	*tmp;

	i = 0;
	tmp = cmd->env_head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", 4) == 0)
		{
			path = tmp->value;
			return (ft_split(path, ':'));
		}
		tmp = tmp->next;
	}
	return (NULL);
}
