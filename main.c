/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:47 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/05 16:53:36 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_status;

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp -> next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;
	char	*new_string;

	new_string = NULL;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_string = ft_strdup(content);
	new_node -> content = new_string;
	new_node -> next = NULL;
	new_node -> prev = NULL;
	if (!new_string)
		return (NULL);
	return (new_node);
}

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return (NULL);
	if (!(*lst))
	{
		*lst = new;
		return (NULL);
	}
	last = ft_lstlast(*lst);
	last -> next = new;
	new->prev = last;
	return (new);
}

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

static void	parse_n_execute(t_cmd *cmd, char *line, t_list **my_env)
{
	int	*hd_cnt;

	hd_cnt = malloc(sizeof(int));
	*hd_cnt = 0;
	line_parse(cmd, line);
	// print_list(cmd->chunk_head);
	syntex_check(cmd);
	convert_tree(cmd);
	// print_tree(cmd->tree_head);
	// print_env(cmd->env_head);
	search_hd(cmd->tree_head, my_env, hd_cnt);
	search_tree(cmd->tree_head, cmd);
	//execute cmd with parse tree
}

void	cpy_env(t_list **env, char **envp)
{
	char	**tmp;
	int		env_cnt;
	int		i;

	tmp = envp;
	env_cnt = 0;
	while (*tmp)
	{
		env_cnt++;
		tmp++;
	}
	i = -1;
	while (++i < env_cnt)
		ft_lstadd_back(env, ft_lstnew(envp[i]));
	return ;
}

char	**lst_to_table(t_cmd *cmd)
{
	char	**table;
	int		env_cnt;
	int		i;
	t_env_lst	*tmp;
	char	*str_tmp;

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

	t_list **my_env = malloc(sizeof(t_list **));
	cpy_env(my_env, envp);
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
		{
			parse_n_execute(&cmd, line, my_env);
			free_all(&cmd, line);
		}
		else
			free(line);
	}
	signal_init(1, 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
