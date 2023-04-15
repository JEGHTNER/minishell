#include "minishell.h"

static void	cmd_init(t_cmd *cmd)
{
	cmd->chunk_head = 0;
	cmd->tree_head = 0;
}

void	line_parse(t_cmd *cmd, char *line)
{
	int	pipe;
	int	quote;

	cmd_init(cmd);
	pipe = 0;
	quote = 0;
	while (*line)
	{
		if (*line == '|')
			manage_pipe(cmd, line, quote);
		else if (*line == '\'' || *line == '\"')
			manage_quotation(cmd, line);
		else if ((*line == '\\' || *line == ';'))
			//exit
		else if (is_whitespace(*line) == YES)
			line++;
		else
		{
			//not whitespace
			manage_chunk(cmd, line);
		}
	}
}
