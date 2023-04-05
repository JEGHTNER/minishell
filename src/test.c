/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:02:23 by jehelee           #+#    #+#             */
/*   Updated: 2023/04/05 21:08:42 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_jehelee.h"
#include <string.h>

char    **cpy_env(char **envp)
{
    char **tmp;
	char **my_env;
	int	env_cnt = 0;
	int	i;

    tmp = envp;
	
    while (*tmp)
    {
        // printf("%s\n", *tmp);
		env_cnt++;
        tmp++;
    }
	my_env = malloc(sizeof(char *) * (env_cnt + 1));
	i = -1;
	while (++i < env_cnt)
		my_env[i] = strdup(envp[i]);
	my_env[i] = NULL;
	return (my_env);
}

int main(int ac, char ** av, char **envp)
{
    char *value;
    char **my_env = NULL;

	if (ac)
		;
	if (av)
		;
    my_env = cpy_env(envp);
	char **tmp = my_env;
	while (*tmp)
    {
        printf("%s\n", *tmp);
        tmp++;
    }
    value = getenv("PATH");

    if (value != NULL)
    {
        // printf("%s=%s\n", "PATH", value);
        // printf("%s=%s\n", environ);
    }
    return 0;
}
