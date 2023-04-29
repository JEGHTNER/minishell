/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <joon-lee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:06:54 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/10 12:06:56 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

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
#include "libft/libft.h"

typedef enum e_cat
{
	WORD,
	W_SINGLE,
	W_DOUBLE,
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
	struct s_token	*left;
	struct s_token	*right;
}	t_token;

typedef struct s_cmd
{
	struct s_env_lst	*env_head;
	struct s_element	*chunk_head;
	struct s_token		*tree_head;
}	t_cmd;

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
t_token	*make_pipe_token(void);

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
void	search_tree(t_token *node);
void	aaa(void);

#endif
