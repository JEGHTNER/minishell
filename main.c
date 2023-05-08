/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:47 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:03:38 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void aaa(void)
{
	system("leaks minishell | grep leaked");
}

int	g_exit_status;

static void	init_main(t_cmd *cmd, char **envp)
{
	struct termios	term;

	cmd_init(cmd);
	init_env_lst(cmd, envp);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal_init(2, 2);
}

static void	parse_n_execute(t_cmd *cmd, char *line)
{
	int	*hd_cnt;

	hd_cnt = malloc(sizeof(int));
	if (!hd_cnt)
		ft_exit_with_error("malloc error\n", 0);
	*hd_cnt = 0;
	line_parse(cmd, line);
	syntex_check(cmd);
	convert_tree(cmd);
	print_tree(cmd->tree_head);
	// search_hd(cmd->tree_head, hd_cnt);
	// search_tree(cmd->tree_head, cmd);
	free(hd_cnt);
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

void	read_line_loop(char *line, t_cmd *cmd)
{
	while (1)
	{
		line = readline("MINISHELL $ ");
		if (!line)
			break ;
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
}

int	main(int ac, char **av, char **envp)
{
	atexit(aaa);
	struct termios	term;
	char			*line;
	t_cmd			cmd;

	if (ac != 1)
		ft_exit_with_error("wrong number of argument\n", 0);
	tcgetattr(STDIN_FILENO, &term);
	init_main(&cmd, envp);
	read_line_loop(line, &cmd);
	signal_init(1, 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
