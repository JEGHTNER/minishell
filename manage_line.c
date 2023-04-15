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

void	manage_quotation(t_cmd *cmd, char *line, size_t *idx, size_t *pipe)
{

}

void	manage_chunk(t_cmd *cmd, char *line, size_t *idx);
