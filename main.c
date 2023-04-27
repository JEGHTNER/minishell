/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:47 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/17 15:26:48 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
	line_parse(cmd, line);
	print_list(cmd->chunk_head);
	syntex_check(cmd);
	convert_tree(cmd);
	print_tree(cmd->tree_head);
	// print_env(cmd->env_head);
	// search_tree(cmd->tree_head);
	//execute cmd with parse tree
}

void	aaa(void)
{
	system("leaks minishell | grep leaked");
}

int main(int ac, char **av, char **envp)
{
	struct termios	term;
	char			*line;
	t_cmd			cmd;

	if (av == 0)
		av = 0;
	if (ac != 1)
		ft_exit_with_error("wrong number of argument", 0);
	tcgetattr(STDIN_FILENO, &term);
	init_main(&cmd, envp);
	while (1)
	{
		line = readline("MINISHELL $");
		if (!line)
			break ;
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && is_everything_whitespace(line) == NO)
			parse_n_execute(&cmd, line);
		free_all(&cmd, line);
		aaa();
	}
	signal_init(1, 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
