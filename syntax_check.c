#include "minishell.h"

// void	pipe_syntax_check(t_list *cur)
// {

// }

// void	redir_syntax_check(t_list *cur)
// {

// }

// void	cmd_syntax_check(t_list *cur)
// {

// }

// void	syntax_check(t_cmd *cmd)
// {
// 	t_list	*cur;

// 	cur = cmd->chunk_head;
// 	while (cur)
// 	{
// 		if (ft_strncmp((char *)cur->content, "|", 2) == 0)
// 			pipe_syntax_check(cur);
// 		else if (ft_strncmp((char *)cur->content, ">>", 3) == 0
// 				|| ft_strncmp((char *)cur->content, "<<", 3) == 0
// 				|| ft_strncmp((char *)cur->content, ">", 2) == 0
// 				|| ft_strncmp((char *)cur->content, "<", 2) == 0)
// 			redir_syntax_check(cur);
// 		else
// 			cmd_syntax_check(cur);
// 		cur = cur->next;
// 	}
// }
