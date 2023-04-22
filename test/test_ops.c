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
