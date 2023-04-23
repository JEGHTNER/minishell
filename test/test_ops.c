#include "../minishell.h"
#include <stdio.h>

void print_list(t_element *head)
{
	size_t	idx = 1;

	while (head)
	{
		printf("list no.%zu\t:\t%s\n", idx, head->content);
		head = head->next;
		idx++;
	}
}

void print_tree(t_token *head)
{
	if (head == 0)
		return ;
	print_tree(head->left);
	for (int i = 0; i < head->argc; i++)
		printf(" %s ", head->argv[i]);
	printf("\n");
	print_tree(head->right);
}
