/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_jehelee.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:41:51 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/18 23:49:59 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_JEHELEE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include "./lib/include/ft_printf.h"
# include "./lib/include/get_next_line.h"
# include "./lib/include/libft.h"
# include "./lib/include/pipex_bonus.h"

typedef struct s_env_lst
{
	t_list	*next;
	t_list	*prev;
	char	*env_string;
}	t_env_lst;

// typedef struct s_pipex
// {
// 	int		fd_infile;
// 	int		fd_outfile;
// 	int		pipe[2];
// 	int		here_doc_flag;
// 	char	*limiter;
// 	char	**envp_args;
// 	char	**path_args;
// 	t_list	*pid_list;
// 	pid_t	pid;
// }			t_pipex;


//built_in_func.c
void	ft_exit(char **arguments);
void	echo(char *str, int option);
void	env(t_list **my_env);
void	unset(t_list **my_env, char *string);
void	pwd(void);


//built_in_func2.c
void	cd(t_list **my_env, char *go_path);
void	export(t_list **my_env, char *string);

//built_in_utils.c
t_list	*find_env(t_list **my_env, char *string);
int	argument_check(char *string);
void sort_env(t_list **my_env);
int	check_isdigit(char *string);
void	check_exit_arguments(char **arguments);

//bulit_in_utils2.c
void	del_env(t_list **my_env, t_list *find);

//pipe functions
char	**get_path_args(t_list **my_env);

#endif