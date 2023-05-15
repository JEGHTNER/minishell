/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:06:54 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/14 23:11:27 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft/libft.h"

typedef enum s_pipe_fd
{
	READ,
	WRITE
}	t_pipe_fd;

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
}	t_is_builtin;

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
	int					back_up_fd[2];
}	t_cmd;

extern int	g_exit_status;
//manage environment variable utils
void		add_env_list(t_cmd *cmd, char *key, char *value);
void		init_env_lst(t_cmd *cmd, char **envp);
char		*find_value_with_key(t_env_lst *head, char *to_find);
t_macro		is_it_env_key(char check);

//manage signal(SIGINT, SIGQUIT)
void		signal_init(int sig_int, int sig_quit);
void		signal_init_heredoc(void);
void		signal_init_default(void);

//split line & make list
t_macro		line_parse(t_cmd *cmd, char *line);
void		insert_node(char *data, t_cmd *cmd, t_cat type);
size_t		find_node(char *to_find, t_cmd *cmd);
t_element	*ft_lstnew_mini(char *content);
void		ft_lstadd_back_mini(t_element **lst, t_element *new);
void		ft_free_list(t_element **head);

//manage quotation

t_macro		manage_quotation(t_cmd *cmd, char *line, size_t *idx);
char		*double_quote_to_string(t_cmd *cmd, char *line, size_t *idx, \
			size_t *st);
char		*single_quote_to_string(char *line, size_t *idx, size_t *st);

//manage quotation utils
t_macro		check_side_quotation(char *line, size_t *start, size_t *end_idx);
char		*quote_to_string(t_cmd *cmd, char *line, size_t *idx, size_t *st);
t_macro		nothing_to_ret(char **tmp, size_t *idx, size_t end_idx, \
			size_t *st);
char		*trim_before_conv(char *data, char *line, size_t *st, size_t *idx);

//manage pipe, redir & chunk
t_macro		manage_pipe(t_cmd *cmd, char *line, size_t *idx);
t_macro		manage_redir(t_cmd *cmd, char *line, size_t *idx);
t_macro		manage_chunk(t_cmd *cmd, char *line, size_t *idx);

//manage env variable
t_macro		manage_env(t_cmd *cmd, char *line, size_t *idx);
char		*find_n_convert(t_cmd *cmd, char *line, size_t *idx, size_t *st);
char		*convert_exit_stat(size_t *idx, size_t *st);
char		*convert_null(size_t *idx, size_t *st);

//syntax check
t_macro		syntex_check(t_cmd *cmd);

//convert list to token
t_token		*change_element_token(t_element *tmp);
t_token		*make_word_token(t_element *tmp);
t_token		*make_redir_token(t_element *tmp);
t_token		*make_pipe_token(t_element *tmp);

//put token into tree
void		convert_tree(t_cmd *cmd);

//tree_ops
t_token		*init_token(t_cat type);
void		insert_cmd(t_token **head, t_token *to_put);
void		insert_pipe(t_token **head, t_token *to_put);
void		insert_redir(t_token **head, t_token *to_put);

//parse tree utils
t_token		*init_redir_token(t_token *to_put, int flag);
void		div_redir_token(t_token *cur, t_token *to_put);
void		insert_cmd_when_head_pipe(t_token *cur, t_token *tmp, \
			t_token *to_put);
void		insert_redir_when_head_pipe(t_token *cur, t_token *to_put);

//general utils
void		cmd_init(t_cmd *cmd);
void		ft_exit_with_error(char *message, char *specifier);
char		*strchop(char *src, size_t start, size_t end);
t_macro		is_whitespace(char tmp);
t_macro		is_everything_whitespace(char *tmp);
char		*chop_n_trim(char *data, char *line, size_t *start_idx, \
			size_t *idx);
char		*join_n_free(char *former, char *latter);
t_macro		error_n_ret(char *to_print);
char		*free_n_ret(char *to_free);
int			for_chunk(char bite);
t_macro		is_it_in_charset(char checker, char *charset);

//free utils
void		free_all(t_cmd *cmd, char *line);
void		ft_free_tree(t_token **head);
void		ft_free_list(t_element **head);
void		ft_free_list_err(t_element **head);

//test
void		print_list(t_element *head);
void		print_env(t_env_lst *head);
void		print_tree(t_token *head);
// void	search_tree(t_token *node, t_list **my_env);

//pipe functions
// char	**get_path_args(t_list **my_env);
char		**get_path_args(t_cmd *cmd);
char		*get_path(char *cmd, char **path_args);

//tree_func.c
void		search_tree(t_token *node, t_cmd *cmd);
int			execute_tree(t_token *node, t_cmd *cmd);

//tree_utils.c
void		exec_redirs(t_token *node);
void		exec_redir(t_token *node, t_cmd *cmd);
void		exec_pipe(t_token *node);
void		exec_cmd(t_token *node);
void		exec_scmd(t_token *node, t_cmd *cmd);

//tree_utils_redir.c
void		exec_redir_case_dr(t_token *node);
void		exec_redir_case_r(t_token *node);
void		exec_redir_case_l(t_token *node, t_cmd *cmd);

//tree_utils_scmd_parent.c
void		parent_pipe(t_token *node);
void		parent_process(t_token *node, t_cmd *cmd, int is_builtin, int pid);
void		parent_wait(t_token *node, int is_builtin, int pid);
void		parent_redir_last(t_token *node, t_cmd *cmd, int is_builtin);

//tree_utils_scmd_child.c
void		child_redir(t_token *node, int is_builtin, t_cmd *cmd);
void		child_pipe(t_token *node, int is_builtin, t_cmd *cmd);
void		child_last(t_token *node, int is_builtin, t_cmd *cmd);
void		child_process(t_token *node, t_cmd *cmd, int is_builtin);
void		ft_execute(char *path, char **argv, char **env_table);

//tree_uilts_builtin.c
int			do_builtin(int is_builtin, t_token *node, t_cmd *cmd);
int			do_builtin2(int is_builtin, t_token *node, t_cmd *cmd);
int			check_builtin(char *str);

//here_doc.c
void		here_doc_tmp(t_cmd *cmd, char *limiter, int index, int *hd_fail);
void		here_doc(t_token *node);
void		search_hd(t_cmd *cmd, t_token *node, int *hd_cnt, int *hd_fail);

//here_doc_utils.c
char		*here_doc_parsing(t_cmd *cmd, char *line);

//lst_to_table
// char	**lst_to_table(t_list **my_env);
char		**lst_to_table(t_cmd *cmd);
void		printenv(t_list **my_env);

//built_in_func.c
int			ft_exit(char **arguments);
void		echo(char **argv);
void		env(t_cmd *cmd);
void		unset(t_cmd *cmd, char **argv);
void		pwd(void);

//built_in_func2.c
void		cd(t_cmd *cmd, char **argv);
void		export(t_cmd *cmd, char **argv);

//built_in_utils.c
t_env_lst	*find_env(t_cmd *cmd, char *string);
int			argument_check(char *string);
int			check_isdigit(char *string);
int			check_exit_arguments(char **arguments);
int			check_exit_arguments_err(int cnt, char *argument);

//bulit_in_utils2.c
void		del_env(t_cmd *cmd, t_env_lst *find);
void		echo_n(char **argv);
int			get_echo_option(char *str);
void		sort_env(t_cmd *cmd);

//built_in_utils_cd.c
int			cd_home_check(t_cmd *cmd, char **argv);
void		refresh_path(char *path, t_cmd *cmd, char *new_path);
void		check_a_path(char *path, t_cmd *cmd);
int			check_r_path(char *path, t_cmd *cmd, char **argv, char **new_path);
void		put_err_path(char **new_path, char **argv);

//ft_split_export.c
char		**ft_split_export(char const *string, char seperator);
char		**free_words(char **words);

int			do_builtin(int is_builtin, t_token *node, t_cmd *cmd);
int			do_builtin2(int is_builtin, t_token *node, t_cmd *cmd);
void		print_tree(t_token *head);

#endif
