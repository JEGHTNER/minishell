#include "minishell.h"

void	free_all(t_cmd *cmd, char *line)
{
	free(line);
	ft_free_list(&(cmd->chunk_head));
	ft_free_tree(&(cmd->tree_head));
}

void	ft_free_tree(t_token **head)
{
	size_t	idx;

	idx = 0;
	if ((*head)->left)
		ft_free_tree(&((*head)->left));
	if ((*head)->right)
		ft_free_tree(&((*head)->right));
	if ((*head)->argc != 0)
	{
		while (idx < (size_t)((*head)->argc))
			free(((*head)->argv)[idx++]);
		free((*head)->argv);
	}
	free(*head);
	*head = 0;
}

void	ft_free_list(t_element **head)
{
	t_element	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
	head = 0;
}
