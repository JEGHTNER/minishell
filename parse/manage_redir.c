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

static t_macro	manage_append_output_redir(t_cmd *cmd, char *line, size_t *idx)
{
	char	mark;

	mark = line[*idx];
	(*idx) += 2;
	if (line[*idx] == '\0' || is_everything_whitespace(line + *idx) == YES
		|| is_it_adequate_for_filename(line[*idx]) == NO)
		return (error_n_ret("syntax error near unexpected token\n"));
	else
	{
		if (mark == '>')
			insert_node(ft_strdup(">>"), cmd, REDIR);
		else
			insert_node(ft_strdup("<<"), cmd, REDIR);
		return (YES);
	}
}

static t_macro	manage_std_output_redir(t_cmd *cmd, char *line, size_t *idx)
{
	char	mark;

	mark = line[*idx];
	(*idx)++;
	if (line[*idx] == '\0' || is_everything_whitespace(line + *idx) == YES
		|| is_it_adequate_for_filename(line[*idx]) == NO)
		return (error_n_ret("syntax error near unexpected token\n"));
	else
	{
		if (mark == '>')
			insert_node(ft_strdup(">"), cmd, REDIR);
		else
			insert_node(ft_strdup("<"), cmd, REDIR);
		return (YES);
	}
}

t_macro	manage_redir(t_cmd *cmd, char *line, size_t *idx)
{
	if (ft_strncmp(line + *idx, ">>", 2) == 0
		|| ft_strncmp(line + *idx, "<<", 2) == 0)
	{
		if (manage_append_output_redir(cmd, line, idx) == NO)
			return(NO);
	}
	else
	{
		if (manage_std_output_redir(cmd, line, idx) == NO)
			return (NO);
	}
	return (YES);
}
