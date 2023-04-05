/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:16:51 by jehelee           #+#    #+#             */
/*   Updated: 2023/03/05 00:37:17 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
/* malloc, free, exit */
# include <stdlib.h>
/* open, unlink */
# include <fcntl.h>
/* waitpid, wait */
# include <sys/wait.h>
/*for perror*/
# include <stdio.h>
/* libft, ft_printf, get_next_line */
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

//typedefs
typedef enum pipex_status
{
	PIPE_READ,
	PIPE_WRITE,
}	t_pipex_status;

typedef enum awk
{
	NO_AWK,
	AWK,
}	t_awk;

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		pipe[2];
	int		here_doc_flag;
	char	*limiter;
	char	**envp_args;
	char	**path_args;
	t_list	*pid_list;
	pid_t	pid;
}			t_pipex;

//here_doc functions
void		here_doc(char *limiter);
void		here_doc_tmp(char *limiter);
int			is_here_doc(t_pipex *pipex, char *argv_i);

//init_pipex functions
char		**get_path_args(char *envp[]);
int			check_sh(char *cmd);
char		*get_path(char *cmd, char **path_args);
void		init_pipex(t_pipex *pipex, int argc, char **argv, char *envp[]);

//ft_split_pipex function
size_t		ft_strlcpy_pipex(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy_quote(char *dst, const char *src, size_t *i, size_t *j);
void		ft_strlcpy_quote_check(const char *s, size_t *i, char q, int *q_f);
char		**ft_split_pipex(char const *string, char seperator);
char		**ft_split_norm(char const *string, char seperator);
int			check_string(char const *string);
int			check_awk(char const *string);
char		*make_awk(const char *string, int *i);
char		**case_awk(const char *string);
char		*quote_line(char const *string, int i, int str_len, char quote);
char		*make_quote_line(char const *string);
char		**case_sh(const char *string);
int			check_sep(char c, char sep);
int			count_words(char const *string, char seperator);
int			skip_quoted_string(char const *string, int i);
int			find_len(char const *string, int len, char seperator);
char		*make_string(char const *string, char seperator, int *i);

//fork function
void		parent_process(int pipe_fd[2], t_list *pid_list, t_pipex *pipex);
void		child_process(t_pipex *pipex, char **argv, int i, int pipe_fd[2]);
void		first_child_process(t_pipex *pipex, int ac, char **av, int pipe[2]);
void		first_child_heredoc(t_pipex *pipex, int ac, char **av);
void		first_child_infile(t_pipex *pipex, int *i);
void		last_child_process(t_pipex *pipex, char **av, int i, int pipe[2]);
int			wait_func(t_list *pid_list);
void		multi_pipe(t_pipex *pipex, int argc, char *argv[], t_list *p_list);
int			check_heredoc(t_pipex *pipex);
int			ft_w_exit_status(int status);

//error_utils
void		error_handle(t_pipex *pipex, char *argv[], int argc);
void		error_no_cmd(char **cmd_args, char *argv_i);
void		error_no_cmd_path(char *c_path, char *av[], int i);
void		error_no_infile(t_pipex *pipex, char *argv[]);
void		error_no_pipe(t_pipex *pipex);
void		error_no_outfile(t_pipex *pipex, char *argv[], int argc);

//free functions
void		free_pipex(t_pipex *pipex);
char		**free_2d_arr(char **words);
void		ft_lstfree(t_list *lst);
int			ft_w_exit_status(int status);

#endif