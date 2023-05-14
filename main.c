/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:47 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/14 23:07:27 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static void	init_main(t_cmd *cmd, char **envp)
{
	struct termios	term;

	cmd_init(cmd);
	init_env_lst(cmd, envp);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	parse_n_execute(t_cmd *cmd, char *line)
{
	int			hd_cnt;
	int			hd_fail;

	hd_cnt = 0;
	hd_fail = 0;
	line_parse(cmd, line);
	if (g_exit_status == 258)
		return ;
	if (syntex_check(cmd) == NO)
		return ;
	convert_tree(cmd);
	search_hd(cmd, cmd->tree_head, &hd_cnt, &hd_fail);
	if (hd_fail == 1)
		return ;
	search_tree(cmd->tree_head, cmd);
}

char	**lst_to_table(t_cmd *cmd)
{
	char		**table;
	int			env_cnt;
	int			i;
	char		*str_tmp;
	t_env_lst	*tmp;

	tmp = cmd->env_head;
	env_cnt = 0;
	while (tmp)
	{
		env_cnt++;
		tmp = tmp->next;
	}
	table = malloc(sizeof(char *) * (env_cnt + 1));
	i = -1;
	tmp = cmd->env_head;
	while (++i < env_cnt)
	{
		str_tmp = ft_strjoin(tmp->key, "=");
		table[i] = ft_strjoin(str_tmp, tmp->value);
		free(str_tmp);
		tmp = tmp->next;
	}
	table[i] = 0;
	return (table);
}

void	read_line_loop(t_cmd *cmd)
{
	char	*line;

	while (1)
	{
		signal_init(2, 2);
		line = readline("MINISHELL $ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && is_everything_whitespace(line) == NO)
		{
			parse_n_execute(cmd, line);
			free_all(cmd, line);
		}
		else
			free(line);
	}
	close(cmd->back_up_fd[READ]);
	close(cmd->back_up_fd[WRITE]);
}

int	main(int ac, char **av, char **envp)
{
	struct termios	term;
	t_cmd			cmd;

	if (ac != 1)
		ft_exit_with_error("wrong number of argument", 0);
	if (!av)
		av = 0;
	tcgetattr(STDIN_FILENO, &term);
	init_main(&cmd, envp);
	read_line_loop(&cmd);
	signal_init(1, 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
