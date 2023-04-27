/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:26:54 by joon-lee          #+#    #+#             */
/*   Updated: 2023/04/23 12:23:44 by joon-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	pipe_in_chunk(t_cmd *cmd, char *line, size_t *start, size_t *idx)
{
	char *tmp;

	tmp = strchop(line, *start, *idx - 1);
	insert_node(tmp, cmd, WORD);
	manage_pipe(cmd, line, idx);
	*start = *idx;
}

static void	redir_in_chunk(t_cmd *cmd, char *line, size_t *start, size_t *idx)
{
	char *tmp;

	tmp = strchop(line, *start, *idx - 1);
	insert_node(tmp, cmd, WORD);
	manage_redir(cmd, line, idx);
	*start = *idx;
}

// static void	env_in_chunk(t_cmd *cmd, char *line, size_t *start, size_t *idx)
// {
// 	char	*tmp;
// 	char	*key_to_find;

// 	tmp = strchop(line, *start, *idx - 1);
// 	insert_node(tmp, cmd, WORD);
// 	key_to_find =
// }

static void	quote_in_chunk(t_cmd *cmd, char *line, size_t *start, size_t *idx)
{
	char	*tmp;
	char	*data;
	char	quote;

	quote = line[*idx];
	tmp = strchop(line, *start, *idx - 1);
	data = quotation_to_string(line, idx, tmp);
	data = check_remain(line, idx, data);
	if (quote == '\'')
		insert_node(data, cmd, W_SINGLE);
	else
		insert_node(data, cmd, W_DOUBLE);
}

void	manage_chunk(t_cmd *cmd, char *line, size_t *idx)
{
	char	*data;
	size_t	start_idx;

	start_idx = *idx;
	while ((is_whitespace(line[*idx]) == NO && line[*idx]))
	{
		if (line[*idx] == '|')
			pipe_in_chunk(cmd, line, &start_idx, idx);
		else if (line[*idx] == '<' || line[*idx] == '>')
			redir_in_chunk(cmd, line, &start_idx, idx);
		// else if (line[*idx] == '$')
		// 	env_in_chunk(cmd, line, &start_idx, idx);
		else if (line[*idx] == '\'' || line[*idx] == '\"')
			quote_in_chunk(cmd, line, &start_idx, idx);
		if (is_whitespace(line[*idx]) == YES)
			return ;
		(*idx)++;
		if (is_whitespace(line[*idx]) == YES || *idx == ft_strlen(line))
		{
			data = strchop(line, start_idx, *idx - 1);
			insert_node(data, cmd, WORD);
		}
	}
}
