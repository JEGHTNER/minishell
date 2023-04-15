#include "minishell.h"

static void	cmd_init(t_cmd *cmd)
{
	cmd->chunk_head = 0;
	cmd->tree_head = 0;
}

void	line_parse(t_cmd *cmd, char *line)
{
	size_t	pipe;
	size_t	quote;
	size_t	idx;

	cmd_init(cmd);
	pipe = 0;
	quote = 0;
	idx = 0;
	while (line[idx])
	{
		if (line[idx] == '|')
			manage_pipe(cmd, line, &idx, &quote);
		else if (line[idx] == '\'' || line[idx] == '\"')
			manage_quotation(cmd, line, &idx, &pipe);
		else if (line[idx] == '\\' || line[idx] == ';')
			ft_exit_with_error("syntax error near unexpected token\n", *line);
		else if (is_whitespace(line[idx]) == YES)
			idx++;
		else
			manage_chunk(cmd, line, &idx);
	}
}
