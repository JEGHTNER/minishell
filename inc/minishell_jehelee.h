/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_jehelee.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:41:51 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/05 19:51:24 by jehelee          ###   ########.fr       */
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
    t_list  *content;
    t_list  *next;
}               t_env_lst;

#endif