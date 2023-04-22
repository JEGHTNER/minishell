#include "minishell.h"

void    insert_node(char *data, t_cmd *cmd)
{
	t_list	*to_add;

	to_add = ft_lstnew((char *)data);
	if (!to_add)
		ft_exit_with_error("malloc error", 0);
	ft_lstadd_back(&(cmd->chunk_head), to_add);
}

size_t	find_node(char *to_find, t_cmd *cmd)
{
	t_list	*cur;
	size_t	idx;

	idx = 0;
	cur = cmd->chunk_head;
	while (!cur)
	{
		if (ft_strncmp(to_find, cur->content, ft_strlen(to_find)) == 0)
			return (idx);
		cur = cur->next;
		idx++;
	}
	return (0);
}
