/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:02:23 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/19 00:00:30 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"
#include <string.h>

int	argument_check(char *string);

long long	exit_status = 0;

char	**get_path_args(t_list **my_env)
{
	int		i;
	char	*path;
	char	*new_envp;
	t_list	*tmp;

	// if (!my_env || !*my_env)
	// {
	// 	new_envp = "PATH=/usr/local/bin:/usr/bin:/bin";
	// 	if (ft_strncmp(new_envp, "PATH=", 5) == 0)
	// 	{
	// 		path = new_envp + 5;
	// 		return (ft_split(path, ':'));
	// 	}
	// }
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
	// env(my_env);
	char *extest[2] = {"1a", NULL};
	// exec_pipe(my_env, cmd);
	ft_exit(extest);
	printf("exit status: %lld ", exit_status);
	return 0;
}
// int	exec_pipe(t_list *cur_proc, char *cmd, t_list **path_args)
// {
// 	char	**cmd_arr;
// 	int		i;
// 	int		pipe_fd[2];
// 	int		pid;

// 	path = get_path(t_list *cur_proc, )
// 	i = 0;
// 	while (cmd_arr[i])
// 	{
// 		pipe(pipe_fd);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			dup2(fd[1], 1);
// 			close(fd[0]);
// 			close(fd[1]);
// 			execve(cmd_arr[i], cmd_arr, NULL);
// 		}
// 		else
// 		{
// 			dup2(fd[0], 0);
// 			close(fd[0]);
// 			close(fd[1]);
// 			wait(NULL);
// 		}
// 		i++;
// 	}
// }

// void		exec_process(t_list *head, t_list **my_env)
// {
// 	t_list	*cur_proc;
// 	t_cmd	*cmd;
// 	char	**path_args;

// 	path_args = get_path_args(my_env);
// 	cur_proc = head->next;
// 	while (cur_proc != NULL)
// 	{
// 		cmd = cur_proc->content;
// 		if (cmd->cmdlines[0])
// 		{
// 			if (cmd->has_redir == 1)
// 			{
// 				exec_redir(cmd, cmd->cmdlines);
// 				break ;
// 			}
// 			if ((check_builtin(cmd->cmdlines) == TRUE))
// 				exec_builtin(cmd, cmd->cmdlines);
// 			else
// 				exec_pipe(cur_proc, cmd);
// 		}
// 		cur_proc = cur_proc->next;
// 	}
// 	ft_lstclear(&head, free_cmdline);
// }