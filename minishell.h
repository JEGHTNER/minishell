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

typedef enum e_type
{
	CMD,
	REDIR,
	PIPE,
	SEP,
	CTR_OP
}	t_type;

typedef enum e_macro
{
	YES,
	NO
}	t_macro;

typedef struct s_env_lst
{
	struct s_env_lst	*next;
	struct s_env_lst	*prev;
	char				*key;
	char				*value;
}	t_env_lst;

typedef struct s_token
{
	enum e_type		type;
	char 			*data;
	//output
	//input
	//is_env
	//is_pipe
	char			*cmd_path;
	struct s_token	*left;
	struct s_token	*right;
}	t_token;

typedef struct s_cmd
{
	struct s_list	*chunk_head;
	struct s_token	*tree_head;
}	t_cmd;

//manage signal(SIGINT, SIGQUIT)
void	signal_init(void);

//split line & make list
void	line_parse(t_cmd *cmd, char *line);
void    insert_node(char *data, t_cmd *cmd);
size_t	find_node(char *to_find, t_cmd *cmd);

//split line utils
void	manage_pipe(t_cmd *cmd, char *line, size_t *idx, size_t *quote);
void	manage_quotation(t_cmd *cmd, char *line, size_t *idx);
void	manage_chunk(t_cmd *cmd, char *line, size_t *idx);

//syntax check
void	syntex_check(t_cmd *cmd);

//syntax check utils

//convert list to parse tree
void	convert_tree(t_cmd *cmd);

//parse tree utils

//general utils
void	ft_exit_with_error(char *message, char *specifier);
char	*strchop(char *src, size_t start, size_t end);
t_macro	is_whitespace(char tmp);
t_macro is_everything_whitespace(char *tmp);

//test
void print_list(t_list *head);

#endif
