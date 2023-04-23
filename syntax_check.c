#include "minishell.h"

static void	pipe_syntax_check(t_element *cur)
{
	if (cur->next->t_flag == WORD
		|| cur->next->t_flag == W_SINGLE
		|| cur->next->t_flag == W_DOUBLE)
		return ;
	else
		ft_exit_with_error("token syntex error : ", "pipe");

}

static void	redir_syntax_check(t_element *cur)
{
	if (cur->next->t_flag == WORD
		|| cur->next->t_flag == W_SINGLE
		|| cur->next->t_flag == W_DOUBLE)
		return ;
	else
		ft_exit_with_error("token syntex error : ", "io_redirection");
}

// void	word_syntax_check(t_element *cur)
// {
// }

void	syntax_check(t_cmd *cmd)
{
	t_element	*cur;

	cur = cmd->chunk_head;
	while (cur)
	{
		if (cur->t_flag == REDIR)
			redir_syntax_check(cur);
		else if (cur->t_flag == PIPE)
			pipe_syntax_check(cur);
		cur = cur->next;
	}
}
