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
    to_ret->is_pipe = YES;
    to_ret->cmd_path = 0;
    to_ret->left = 0;
    to_ret->right = 0;
    return (to_ret);
}
