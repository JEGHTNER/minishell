/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:02:23 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/19 21:19:25 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"
#include <string.h>

int	argument_check(char *string);
void	search_tree(t_token *node, t_list **my_env);
int	execute_tree(t_token *node, t_list **my_env);
int	exec_pipe(t_token *node);
int	exec_cmd(t_token *node, t_list **my_env);


long long	exit_status = 0;

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

int init_token(t_token *token, char* str, t_list **my_env)
{
	char **path_args;
	char **cmd_args = ft_split(str, ' ');
	path_args = get_path_args(my_env);
	token->cmd_path = get_path(cmd_args[0], path_args);
	token->data = str;
	token->left =NULL;
	token->right =NULL;
	token->pipe_fd = 0;
}

int	main(int ac, char **av, char **envp)
{
	// char	*value;
	t_list	**my_env;
	int		back_up_stdin;
	int		back_up_stdout;

	if (ac)
		;
	if (av)
		;
	back_up_stdin = dup(STDIN_FILENO);
	back_up_stdout = dup(STDOUT_FILENO);
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
	printf("exit status: %lld \n", exit_status);
	t_token *head;
	t_token	first;
	t_token second;
	t_token third;
	
	init_token(&first, "ls -al", my_env);
	init_token(&second, "|", my_env);
	second.type = PIPE;
	init_token(&third, "wc -l", my_env);

	*head = second;
	head->left = &first;
	head->right = &third;
	search_tree(head, my_env);
	dup2(back_up_stdin, STDIN_FILENO);
	dup2(back_up_stdout, STDOUT_FILENO);
	return 0;
}

void	search_tree(t_token *node, t_list **my_env)
{
	execute_tree(node, my_env);
	if (node->left != NULL)
		search_tree(node->left, my_env);
	if (node->right != NULL)
		search_tree(node->right, my_env);
}

int	execute_tree(t_token *node, t_list **my_env)
{
	int pid;
	printf("%s\n",node->data);
	char **argv = ft_split(node->data, ' ');
	if (node->type == PIPE)
		exec_pipe(node);
	// if (node->type == REDIR)
	// 	exec_redir(node);
	// if (node->type == CMD)
	// 	exec_cmd(node);
	pid = fork();
	if (pid == 0)
	{
		exec_cmd(node, my_env);
		// execve(node->cmd_path, argv, my_env);
		exit(2);
	}
	printf("parent\n");

	// wait(NULL);
	// if (node->type == PIPE)
	// 	exec_pipe();
	// if (node->type == CMD)
	// 	exec_cmd(node->data, my_env);
	// if (node->type == REDIR)
	// 	exec_redir();

}

int	exec_pipe(t_token *node)
{
	node->pipe_fd = malloc(sizeof(int *) * 2);
	if (pipe(node->pipe_fd) < 0)
		perror("pipe error");
	if (node->left)
		node->left->pipe_fd = node->pipe_fd;
	if (node->right)
		node->right->pipe_fd = node->pipe_fd;
}

int	exec_cmd(t_token *node, t_list **my_env)
{
	char	**cmd_arr;
	int		i;
	int		pid;
	char	**path_args;
	char	*path;

	char **cmd_args = ft_split(node->data, ' ');
	path_args = get_path_args(my_env);
	path = get_path(cmd_args[0], path_args);
	printf("path = %s\n", path);
	pid = fork();
	if (pid < 0)
		perror("pipe");
	if (pid == 0) // child
	{
		if (node->pipe_fd)
		{
			close(node->pipe_fd[READ]);
			dup2(node->pipe_fd[WRITE], STDOUT_FILENO);
			close(node->pipe_fd[WRITE]);
			if (execve(path, cmd_args, my_env) < 0)
			{
				perror("execve");
				exit(127);
			}
		}
		if (execve(path, cmd_args, my_env) < 0)
		{
			perror("execve");
			exit(127);	
		}
	}
	else // parent
	{
		if (node->pipe_fd)
		{
			close(node->pipe_fd[WRITE]);
			dup2(node->pipe_fd[READ], STDIN_FILENO);
			close(node->pipe_fd[READ]);
		}
	}
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