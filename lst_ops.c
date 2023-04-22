#include "minishell.h"

void	ft_lstadd_back_mini(t_element **lst, t_element *new)
{
	t_element	*temp;

	if (!new || !lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		new->next = 0;
		return ;
	}
	temp = *lst;
	while ((*lst)->next != 0)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
	(*lst) = temp;
}

t_element	*ft_lstnew_mini(char *content)
{
	t_element	*temp;

	temp = (t_element *)malloc(sizeof(t_element));
	if (!temp)
		return (0);
	temp->content = content;
	temp->next = 0;
	return (temp);
}