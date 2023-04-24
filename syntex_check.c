#include "minishell.h"

static void	pipe_syntax_check(t_element *cur)
{
	if (cur->next->c_flag == WORD
		|| cur->next->c_flag == W_SINGLE
		|| cur->next->c_flag == W_DOUBLE)
		return ;
	else
		ft_exit_with_error("token syntex error : ", "pipe");

}

static void	redir_syntax_check(t_element *cur)
{
	if (cur->next->c_flag == WORD
		|| cur->next->c_flag == W_SINGLE
		|| cur->next->c_flag == W_DOUBLE)
		return ;
	else
		ft_exit_with_error("token syntex error : ", "io_redirection");
}

// void	word_syntax_check(t_element *cur)
// {
// }

void	syntex_check(t_cmd *cmd)
{
	t_element	*cur;

	cur = cmd->chunk_head;
	while (cur)
	{
		if (cur->c_flag == REDIR)
			redir_syntax_check(cur);
		else if (cur->c_flag == PIPE)
			pipe_syntax_check(cur);
		cur = cur->next;
	}
}
