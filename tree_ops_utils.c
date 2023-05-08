#include "minishell.h"

t_token	*init_redir_token(t_token *to_put, int flag)
{
	t_token *tmp_redir;
	t_token	*tmp_cmd;
	t_token	*tmp_sim_cmd;
	t_token	*tmp_pipe;

	tmp_redir = init_token(REDIRS);
	tmp_redir->left = to_put;
	if (flag == 0 || flag == 2)
	{
		tmp_cmd = init_token(CMD);
		tmp_sim_cmd = init_token(SIMPLE_CMD);
		tmp_cmd->left = tmp_redir;
		tmp_cmd->right = tmp_sim_cmd;
		if (flag == 2)
		{
			tmp_pipe = init_token(PIPE);
			tmp_pipe->left = tmp_cmd;
			return (tmp_pipe);
		}
		return (tmp_cmd);
	}
	else
		return (tmp_redir);
}

void	div_redir_token(t_token **cur, t_token *to_put)
{
	if ((*cur)->left == 0)
		(*cur)->left = init_redir_token(to_put, 1);
	else
	{
		(*cur) = (*cur)->left;
		while ((*cur)->right)
			(*cur) = (*cur)->right;
		(*cur)->right = init_redir_token(to_put, 1);
	}
}