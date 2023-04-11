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

typedef struct s_env_lst
{
	struct s_env_lst	*next;
	struct s_env_lst	*prev;
	char				*key;
	char				*value;
}	t_env_lst;

typedef enum e_type
{
	CMD,
	REDIR,
	PIPE,
	SEP,
	CTR_OP
}	t_type;

typedef struct s_token
{
	enum e_type		type;
	char 			*data;
}	t_token;

//manage signal(SIGINT, SIGQUIT)
void	signal_init(void);

#endif
