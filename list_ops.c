#include "minishell.h"

void    insert_node(char *data, t_cmd *cmd)
{
	t_list	*to_add;

	to_add = ft_lstnew((char *)data);
	if (!to_add)
		ft_exit_with_error("malloc error", 0);
	ft_lstadd_back(&(cmd->chunk_head), to_add);
}