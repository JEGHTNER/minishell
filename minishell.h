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

//manage environment variable
void	add_env_list(t_cmd *cmd, char *key, char *value);
void	rm_env_list(t_cmd *cmd, char *key);
void	init_env_lst(t_cmd *cmd, char **envp);
char	*find_value_with_key(t_env_lst *head, char *to_find);
void	manage_env(t_cmd *cmd, char *line, size_t *idx);

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
char	*quotation_to_string(char *line, size_t *idx, char *data);
char	*pipe_after_quote(char *data, char *line, size_t *idx);
char	*check_remain(char *line, size_t *idx, char *data);

//manage pipe, redir & chunk
void	manage_pipe(t_cmd *cmd, char *line, size_t *idx);
void	manage_redir(t_cmd *cmd, char *line, size_t *idx);
void	manage_chunk(t_cmd *cmd, char *line, size_t *idx);

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
void	ft_free_tree(t_token **head);
void	insert_cmd(t_token **head, t_token *to_put);
void	insert_pipe(t_token **head, t_token *to_put);
void	insert_redir(t_token **head, t_token *to_put);

//general utils
void	cmd_init(t_cmd *cmd);
void	ft_exit_with_error(char *message, char *specifier);
char	*strchop(char *src, size_t start, size_t end);
t_macro	is_whitespace(char tmp);
t_macro	is_everything_whitespace(char *tmp);
void	free_all(t_cmd *cmd, char *line);

//test
void	print_list(t_element *head);
void	print_env(t_env_lst *head);
void	print_tree(t_token *head);
void	search_tree(t_token *node);

#endif
