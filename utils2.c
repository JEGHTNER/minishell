#include "minishell.h"

void	cmd_init(t_cmd *cmd);
{
    cmd->env_head = 0;
	cmd->chunk_head = 0;
	cmd->tree_head = 0;
}