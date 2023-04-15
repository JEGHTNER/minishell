#include "minishell.h"

void	init_main(int ac, char **av, char **envp, t_env_lst **env_list)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal_init();
	// initiate env list
}

int main(int ac, char **av, char **envp)
{
	struct termios	term;
	char			*line;
	t_cmd			cmd;
	t_env_lst		**env_lst;

	if (ac != 1)
		exit(0);
	tcgetattr(STDIN_FILENO, &term);
	init_main(ac, av, envp, env_lst);
	while (1)
	{
		line = readline("MINISHELL $");
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			line_parse(&cmd, line);
			syntax_check(&cmd);
			convert_tree(&cmd);
			//execute cmd with parse tree
		}
		ft_free(&cmd, line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
