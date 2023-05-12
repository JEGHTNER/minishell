/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:41:10 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/12 17:36:44 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_dir(char *cmd)
{
	DIR	*is_dir;

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
	return ("not dir");
}

char	*get_path_norm(char *cmd, char **path_args)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	while (path_args[++i])
	{
		tmp = ft_strjoin(path_args[i], "/");
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, X_OK) == 0)
			return (tmp2);
		free(tmp2);
	}
	return (NULL);
}

char	*get_path(char *cmd, char **path_args)
{
	if (!cmd)
		return (NULL);
	if (ft_strncmp(cmd, "", 1) == 0)
		exit(0);
	if (!check_dir(cmd))
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (!path_args)
		return (NULL);
	return (get_path_norm(cmd, path_args));
}

char	**get_path_args(t_cmd *cmd)
{
	char		*path;
	t_env_lst	*tmp;

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
