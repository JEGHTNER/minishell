/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:23:57 by joon-lee          #+#    #+#             */
/*   Updated: 2023/05/08 05:02:54 by jehelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_macro	is_it_adequate_for_filename(char check)
{
	if (ft_isalnum((int)check) == 1)
		return (YES);
	else if (check == '>' || check == '<' || check == '|' || check == ')'
		|| check == '(' || check == '*' || check == '.' || check == '/')
		return (NO);
	else
		return (YES);
}

static void	manage_append_output_redir(t_cmd *cmd, char *line, size_t *idx)
{
	char	mark;

	mark = line[*idx];
	(*idx) += 2;
	if (line[*idx] == '\0' || is_everything_whitespace(line + *idx) == YES
		|| is_it_adequate_for_filename(line[*idx]) == NO)
		ft_exit_with_error("syntax error near unexpected token", ">>, <<");
	else
	{
		if (mark == '>')
			insert_node(ft_strdup(">>"), cmd, REDIR);
		else
			insert_node(ft_strdup("<<"), cmd, REDIR);
	}
}

static void	manage_std_output_redir(t_cmd *cmd, char *line, size_t *idx)
{
	char	mark;

	mark = line[*idx];
	(*idx)++;
	if (line[*idx] == '\0' || is_everything_whitespace(line + *idx) == YES
		|| is_it_adequate_for_filename(line[*idx]) == NO)
		ft_exit_with_error("syntax error near unexpected token", ">, <");
	else
	{
		if (mark == '>')
			insert_node(ft_strdup(">"), cmd, REDIR);
		else
			insert_node(ft_strdup("<"), cmd, REDIR);
	}
}

void	manage_redir(t_cmd *cmd, char *line, size_t *idx)
{
	if (ft_strncmp(line + *idx, ">>", 2) == 0
		|| ft_strncmp(line + *idx, "<<", 2) == 0)
		manage_append_output_redir(cmd, line, idx);
	else
		manage_std_output_redir(cmd, line, idx);
}
