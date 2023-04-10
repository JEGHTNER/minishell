#include "minishell.h"

t_node	*insert_token(t_node *root, char *data, t_type type)
{
	if (!root)
	{
		root = (t_node *)malloc(sizeof(t_node));
		root->right = 0;
		root->left = 0;
		root->data = data;
		root->type = type;
		return (root);
	}
	else
	{
	}
}
