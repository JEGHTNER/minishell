#include "../minishell.h"
#include <stdio.h>

void print_list(t_list *head)
{
	size_t	idx = 1;

	while (head)
	{
		printf("list no.%zu\t:\t%s\n", idx, (char *)head->content);
		head = head->next;
		idx++;
	}
}
