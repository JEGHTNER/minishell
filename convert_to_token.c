#include "minishell.h"
#include <stdio.h>

t_token	*make_word_token(t_element *tmp)
{
	size_t		idx;
	t_element	*start;
	t_token		*to_ret;

	to_ret = init_token();
	if (!to_ret)
		return (0);
	idx = 0;
	start = tmp;
	while (tmp && (tmp->t_flag == WORD
        || tmp->t_flag == W_SINGLE || tmp->t_flag == W_DOUBLE))
	{
		idx++;
		tmp = tmp->next;
	}
	to_ret->type = CMD;
	to_ret->argc = idx;
	to_ret->argv = (char **)malloc(sizeof(char *) * idx);
	idx = 0;
	while (idx < to_ret->argc)
	{
		to_ret->argv[idx++] = start->content;
		start = start->next;
	}
	return (to_ret);
}

t_token	*make_redir_token(t_element *tmp)
{    
	t_token *to_ret;

	to_ret = init_token();
	if (!to_ret)
		return (0);
	to_ret->type = REDIR;
	to_ret->argc = 2;
	to_ret->argv = (char **)malloc(sizeof(char *) * 2);
	to_ret->argv[0] = tmp->content;
	to_ret->argv[1] = tmp->next->content;
	return (to_ret);
}

t_token	*make_pipe_token(t_element *tmp)
{
	t_token *to_ret;

	to_ret = init_token();
	if (!to_ret)
		return (0);
	to_ret->type = PIPE;
	to_ret->is_pipe = YES;
	to_ret->argc = 1;
	to_ret->argv = (char **)malloc(sizeof(char *) * 1);
	to_ret->argv[0] = "|";
	return (to_ret);
}

t_token	*change_element_token(t_element *tmp)
{
	t_token *to_ret;

	if (tmp->t_flag == WORD
		|| tmp->t_flag == W_SINGLE || tmp->t_flag == W_DOUBLE)
		to_ret = make_word_token(tmp);
	else if (tmp->t_flag == PIPE)
		to_ret = make_pipe_token(tmp);
	else
		to_ret = make_redir_token(tmp);
	if (!to_ret)
			ft_exit_with_error("malloc error", 0);
	return (to_ret);
}