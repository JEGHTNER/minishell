/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_jehelee.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:41:51 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/19 18:49:07 by jehelee          ###   ########.fr       */
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

typedef enum s_pipe_fd
{
	READ,
	WRITE
} t_pipe_fd;

typedef enum e_type
{
	CMD,
	REDIR,
	PIPE,
	SEP,
	CTR_OP
}	t_type;

typedef struct s_env_lst
{
	t_list	*next;
	t_list	*prev;
	char	*env_string;
}	t_env_lst;

typedef struct s_token
{
	enum e_type		type;
	char 			*data;
	//output
	//input
	//is_env
	//is_pipe
	int				*pipe_fd;
	char			*cmd_path;
	struct s_token	*left;
	struct s_token	*right;
}	t_token;

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