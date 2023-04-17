/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:54 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/17 15:26:55 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_pipe(t_cmd *cmd, char *line, size_t *idx, size_t *quote)
{
	t_list *tmp;


	if (cmd->chunk_head == 0)
		ft_exit_with_error("syntax error near unexpected token", "`|'");
	else
	{
		if (line[*idx + 1] == '|')
			ft_exit_with_error("syntax error", "||");
		if (line[*idx + 1] == '\0')
			ft_exit_with_error("syntax error for pipe", 0);
		tmp = ft_lstnew((char *)"|");
		if (!tmp)
			ft_exit_with_error("malloc error", 0);
		ft_lstadd_back(&(cmd->chunk_head), tmp);
	}
}

static size_t	check_side_quotation(char *line, size_t start)
{
	size_t	end_idx;
	char	quote;
	int 	flag;

	end_idx = ft_strlen(line) - 1;
	quote = line[start];
	if (line[start] == '\'')
		flag = 0;
	else
		flag = 1;
	while (start <= end_idx)
	{
		if (line[end_idx] == quote)
			break ;
		end_idx--;
	}
	if (start == end_idx)
		ft_exit_with_error("syntax error: side quotation didn't match", 0);
	return (end_idx);
}

static void		check_quotation_match(char *line, size_t start, size_t end)
{

}

void	manage_quotation(t_cmd *cmd, char *line, size_t *idx, size_t *pipe)
{
	char	*data;
	int 	flag;
	size_t	end_idx;
	char	quote;

	end_idx = check_side_quotation(line, *idx);
	check_quotation_match(line, *idx, end_idx);
	quote = line[*idx];
	while(1)
	{

	}

}

void	manage_chunk(t_cmd *cmd, char *line, size_t *idx)
{

}
