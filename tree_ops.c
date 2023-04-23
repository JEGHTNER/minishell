#include "minishell.h"

t_token *init_token(void)
{
    t_token *to_ret;

    to_ret = (t_token *)malloc(sizeof(t_token));
    if (!to_ret)
        return (0);
    to_ret->argv = 0;
    to_ret->argc = 0;
    to_ret->is_env = NO;
    to_ret->is_pipe = NO;
    to_ret->cmd_path = 0;
    to_ret->left = 0;
    to_ret->right = 0;
    return (to_ret);
}

void	insert_cmd(t_token **head, t_token *to_put)
{
    t_token *tmp;
    t_token *redirs;
    t_token *cur;

    tmp = init_token();
    redirs = init_token();
    if (!tmp || !redirs)
        ft_exit_with_error("malloc error", 0);
    tmp->cat = CMD;
    redirs->cat = REDIRS;
    tmp->right = to_put;
    tmp->left = redirs;
    if ((*head) == 0)
        (*head) = tmp;
    else
    {
        cur = (*head);
        while (cur->right != 0 || cur->right->cat == PIPE)
            cur = cur->right;
        cur->left = tmp;
    }
}

void	insert_pipe(t_token **head, t_token *to_put)
{
    t_token *cur;
    t_token *tmp;

    cur = (*head);
    tmp = init_token();
    if (!tmp)
        ft_exit_with_error("malloc error", 0);
    tmp->cat = PIPE;
    tmp->right = tmp;
    if (cur->cat == CMD)
    {
        tmp->left = cur;
        (*head) = tmp;
    }
    else //PIPE
    {
        while (cur->right != 0 || cur->right->cat == PIPE)
            cur = cur->right;
    }
}
void	insert_redir(t_token **head, t_token *to_put)
{

}
