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

typedef struct s_chunk
{
	char			*data;
	struct s_chunk	*next;
}	t_chunk;

typedef struct s_cmd
{
	struct s_chunk	*chunk_head;
	struct s_token	*head;
}	t_token;

//manage signal(SIGINT, SIGQUIT)
void	signal_init(void);

//split line

#endif
