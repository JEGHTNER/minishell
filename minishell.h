/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:06:54 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/05 19:59:44 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
// # define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <termios.h>
#include <term.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef enum s_pipe_fd
{
	READ,
	WRITE
} t_pipe_fd;

typedef enum e_is_builtin
{
	NOT,
	ECH,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
} t_is_builtin;

typedef enum e_cat
{
	WORD,
	CMD,
	SIMPLE_CMD,
	REDIRS,
	REDIR,
	PIPE
}	t_cat;


typedef enum e_macro
{
	YES,
	NO
}	t_macro;

typedef struct s_env_lst
{
	char				*key;
	char				*value;
	struct s_env_lst	*next;
	struct s_env_lst	*prev;
}	t_env_lst;

typedef struct s_element
{
	enum e_cat			c_flag;
	char				*content;
	struct s_element	*next;
}	t_element;

typedef struct s_token
{
	enum e_cat		cat;
	char			**argv;
	int				argc;
	enum e_macro	is_env;
	enum e_macro	is_pipe;
	char			*cmd_path;
	int				back_up_fd[2];
	int				last_flag;
	int				*fail_flag;
	int				*redirect_flag;
	int				*pipe_fd;
	int				*is_hd;
	int				hd_index;

	struct s_token	*left;
	struct s_token	*right;
}	t_token;

typedef struct s_cmd
{
	struct s_env_lst	*env_head;
	struct s_element	*chunk_head;
	struct s_token		*tree_head;
}	t_cmd;

extern int exit_status;
//manage environment variable utils
void	add_env_list(t_cmd *cmd, char *key, char *value);
void	init_env_lst(t_cmd *cmd, char **envp);
char	*find_value_with_key(t_env_lst *head, char *to_find);
t_macro	is_it_env_key(char check);

//manage signal(SIGINT, SIGQUIT)
void	signal_init(int sig_int, int sig_quit);

//split line & make list
void		line_parse(t_cmd *cmd, char *line);
void		insert_node(char *data, t_cmd *cmd, t_cat type);
size_t		find_node(char *to_find, t_cmd *cmd);
t_element	*ft_lstnew_mini(char *content);
void		ft_lstadd_back_mini(t_element **lst, t_element *new);
void		ft_free_list(t_element **head);

//manage quotation

void	manage_quotation(t_cmd *cmd, char *line, size_t *idx);
char	*double_quote_to_string(t_cmd *cmd, char *line, size_t *idx, size_t *st);
char	*single_quote_to_string(char *line, size_t *idx, size_t *st);

//manage quotation utils
size_t	check_side_quotation(char *line, size_t start);
char	*quote_to_string(t_cmd *cmd, char *line, size_t *idx, size_t *st);
t_macro	nothing_to_ret(char **tmp, size_t *idx, size_t end_idx);

//manage pipe, redir & chunk
void	manage_pipe(t_cmd *cmd, char *line, size_t *idx);
void	manage_redir(t_cmd *cmd, char *line, size_t *idx);
void	manage_chunk(t_cmd *cmd, char *line, size_t *idx);

//manage env variable
void	manage_env(t_cmd *cmd, char *line, size_t *idx);
char	*find_n_convert(t_cmd *cmd, char *line, size_t *idx, size_t *st);

//syntax check
void	syntex_check(t_cmd *cmd);

//convert list to token
t_token	*change_element_token(t_element *tmp);
t_token	*make_word_token(t_element *tmp);
t_token	*make_redir_token(t_element *tmp);
t_token	*make_pipe_token(t_element *tmp);

//put token into tree
void	convert_tree(t_cmd *cmd);

//parse tree utils
t_token *init_token(void);
void	insert_cmd(t_token **head, t_token *to_put);
void	insert_pipe(t_token **head, t_token *to_put);
void	insert_redir(t_token **head, t_token *to_put);

//general utils
void	cmd_init(t_cmd *cmd);
void	ft_exit_with_error(char *message, char *specifier);
char	*strchop(char *src, size_t start, size_t end);
t_macro	is_whitespace(char tmp);
t_macro	is_everything_whitespace(char *tmp);
char	*chop_n_trim(char *data, char *line, size_t *start_idx, size_t *idx);
char	*join_n_free(char *former, char *latter);

//free utils
void	free_all(t_cmd *cmd, char *line);
void	ft_free_tree(t_token **head);
void	ft_free_list(t_element **head);

//test
void	print_list(t_element *head);
void	print_env(t_env_lst *head);
void	print_tree(t_token *head);
// void	search_tree(t_token *node, t_list **my_env);
void	aaa(void);

//pipe functions
// char	**get_path_args(t_list **my_env);
char	**get_path_args(t_cmd *cmd);
char	*get_path(char *cmd, char **path_args);

//tree_func.c
// void	search_tree(t_token *node, t_list **my_env);
void	search_tree(t_token *node, t_cmd *cmd);
// int		execute_tree(t_token *node, t_list **my_env);
int		execute_tree(t_token *node, t_cmd *cmd);

//tree_utils.c
int	exec_redirs(t_token *node);
int	exec_redir(t_token *node);
int	exec_pipe(t_token *node);
int exec_cmd(t_token *node);
// int	exec_scmd(t_token *node, t_list **my_env);
int	exec_scmd(t_token *node, t_cmd *cmd);

//here_doc.c
void	here_doc_tmp(char *limiter, int index);
void	here_doc(t_token *node);
void	search_hd(t_token *node, t_list **my_env, int *hd_cnt);

//lst_to_table
// char	**lst_to_table(t_list **my_env);
char	**lst_to_table(t_cmd *cmd);
void	printenv(t_list **my_env);

//built_in_func.c
void	ft_exit(char **arguments);
void	echo(char **argv);
void	env(t_cmd *cmd);
void	unset(t_cmd *cmd, char **argv);
void	pwd(void);


//built_in_func2.c
void	cd(t_cmd *cmd, char **argv);
// void	export(t_list **my_env, char **argv);
void	export(t_cmd *cmd, char **argv);

//built_in_utils.c
// t_list	*find_env(t_list **my_env, char *string);
t_env_lst	*find_env(t_cmd *cmd, char *string);
int	argument_check(char *string);
void sort_env(t_cmd *cmd);
int	check_isdigit(char *string);
void	check_exit_arguments(char **arguments);

//bulit_in_utils2.c
void	del_env(t_cmd *cmd, t_env_lst *find);

t_list	*ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);

char	**ft_split_export(char const *string, char seperator);

#endif
