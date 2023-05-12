/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manage2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:11:18 by jehelee           #+#    #+#             */
/*   Updated: 2023/05/11 16:15:06 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler_default(int signo)
{
	if (signo == SIGINT)
		printf("^C\n");
	if (signo == SIGQUIT)
		printf("^\\Quit: 3\n");
}

void	signal_init_default(void)
{
	signal(SIGINT, signal_handler_default);
	signal(SIGQUIT, signal_handler_default);
}
